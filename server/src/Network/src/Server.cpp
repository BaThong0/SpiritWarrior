#include "../include/Server.h"
#include "../../include/logger.h"
void Server::ListenEvent()
{
    while (true)
    {
        ENetEvent event;
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            {
                HandleConnect(event.peer);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                HandleReceive(event.peer, event.packet);
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
            {
                break;
            }
            }
        }
    }
}

void Server::BroadcastPacket(const char *data)
{
    ENetPacket *packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(server, 0, packet);
}

void Server::ParseData(int id, char *data)
{
    int data_type;
    sscanf(data, "%d|", &data_type);

    switch (data_type)
    {
    case 1: // normal messages from client
    {
        char msg[80];
        sscanf(data, "%*d|%[^|]", &msg); // ignore id, get message
        char send_data[1024] = {'\0'};
        sprintf(send_data, "1|%d|%s", id, msg); // pass the id and the message to the data need to send
        BroadcastPacket(send_data);
        break;
    }
    case 2: // send id to the client
    {
        char username[80];
        sscanf(data, "2|%[^\n]", &username); // take the username

        char send_data[1024] = {'\0'};
        sprintf(send_data, "2|%d|%s", id, username); // pass the id and username to the data need to send
        // std::cout << "SEND: " << send_data << "\n";

        BroadcastPacket(send_data); // send to all the clients
        break;
    }
    }
}

void Server::HandleConnect(ENetPeer *peer)
{
    LOG_INFO("A new client connected from %x:%u.\n",
           peer->address.host,
           peer->address.port);

    nextPlayerId++; // each time a new client is connected, ID increments
    nlohmann::json response = {
        {"type", "INITIALIZE_ID"},
        {"data", {{"client_id", nextPlayerId}}},
        {"meta", {{"timestamp", time(nullptr)}}},
        {"status", "success"}};
    ENetPacket *packet = enet_packet_create(response.dump().c_str(), response.dump().size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

void Server::HandleReceive(ENetPeer *peer, ENetPacket *packet)
{
    std::string data(reinterpret_cast<char *>(packet->data));

    try
    {
        auto j = nlohmann::json::parse(data);

        std::string type = j["type"];

        if (type == "CREATE_ROOM")
        {
            std::string room = j["data"]["room_name"];
            int maxPlayers = j["data"]["max_players"];
            std::string mode = j["data"]["mode"];
            LOG_INFO("Create room: %s maxPlayers: %d mode: %s", room, maxPlayers, mode);

            nlohmann::json response = {
            {"type", "CREATE_ROOM_RESPONSE"},
            {"data", {{"room_id", nextRoomId++}}},
            {"meta", {{"request_id", nextPlayerId++}, {"timestamp", time(nullptr)}}},
            {"status", "success"}};
            std::string msg = response.dump();

            ENetPacket *packetTemp = enet_packet_create(
            msg.c_str(),
            msg.size() + 1,
            ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packetTemp);

            m_roomList[nextRoomId].first = *peer;

        }
        else if (type == "START_GAME")
        {
            // nlohmann::json response = {
            // {"type", "START_GAME_RESPONSE"},
            // {"data", {{"room_id", nextRoomId++}}},
            // {"meta", {{"request_id", nextPlayerId++}, {"timestamp", time(nullptr)}}},
            // {"status", "success"}};
            // std::string msg = response.dump();

            // ENetPacket *packetTemp = enet_packet_create(
            // msg.c_str(),
            // msg.size() + 1,
            // ENET_PACKET_FLAG_RELIABLE);
            // enet_peer_send(peer, 0, packetTemp);
            unsigned int current_roomID = j["data"]["room_id"].get<int>();
            LOG_INFO("ROOM_ID: %d", current_roomID);
            m_roomList[current_roomID].second = std::thread(&Server::RoomLoop, this, current_roomID, peer);

            nlohmann::json response = {
            {"type", "START_GAME_RESPONSE"},
            {"status", "success"}};
            std::string msg = response.dump();

            ENetPacket *packetTemp = enet_packet_create(
            msg.c_str(),
            msg.size() + 1,
            ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packetTemp);
        }
        else if(type == "PLAYER_MOVE")
        {
            LOG_INFO("Player X_pos: %d, Y_pos: %d", j["position"]["x"].get<int>(), j["position"]["y"].get<int>());
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "JSON parse error: " << e.what() << "\n";
    }
}

Server::Server()
{
    // Initializes the ENet library (set up sockets, OS, networking stuff)
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occured while initializing ENet.\n");
        return;
    }
    // Registers enet_deinitialization to be called automatically when the program exits.
    atexit(enet_deinitialize);

    address.host = ENET_HOST_ANY; // listen on all available network interfaces
    address.port = 7777;          // server's listening port (clients must connect to this port)

    // /*
    // creates the actual server host. Params:
    // - &address -> bind to 0.0.0.0:7777
    // - 32 -> maximum number of clients that can connect
    // - 1 -> number of channels per connection (like TCP streams inside the ENet)
    // - 0 -> incoming bandwidth (0 = unlimited)
    // - 0 -> outgoing bandwidth (0 = unlimited)
    // */
    server = enet_host_create(&address, 32, 1, 0, 0);

    if (server == NULL)
    {
        fprintf(stderr, "An error occured while trying to create an ENet server host!\n");
        return;
    }

    // Create thread to listen to incoming events
    m_workerListenEvent = std::thread(&Server::ListenEvent, this);

    return;
}

Server::~Server()
{
    enet_host_destroy(server);
    if (m_workerListenEvent.joinable())
        m_workerListenEvent.join();
    enet_deinitialize();
}
void Server::RoomLoop(unsigned int roomId, ENetPeer *peer)
{
    LOG_INFO("Start room loop: %d ...", roomId);

    /* Start room loop */
    while(true)
    {

        //sleep(0.1);
        // LOG_INFO("ROOM GAME IS RUNNING: %d", roomId);
        // int count = 0;
        // nlohmann::json response = {
        //     {"type", "SENDING_DATA_CONTINUOUSLY"},
        //     {"data", {{"position", count++}}},};
        //     std::string msg = response.dump();

        //     ENetPacket *packetTemp = enet_packet_create(
        //     msg.c_str(),
        //     msg.size() + 1,
        //     ENET_PACKET_FLAG_RELIABLE);
        // enet_peer_send(peer, 0, packetTemp);
    }
    LOG_INFO("End room loop: %d", roomId);
}

void Server::Run()
{
    LOG_INFO("Server is running...");

    // GAME LOOP START
    LOG_INFO("Update logic for clients");
    while (true)
    {
        // server uses fixed time steps
        // ProcessEvents() -> consumes requests -> update states
        // UpdateGame()  -> physics, timers, AI, rules
        // BroadcastUpdates() -> send state back to clients
        // SleepUntilNextTick()
    }
}
