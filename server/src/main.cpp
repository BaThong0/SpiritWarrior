#include <iostream>
#include <enet/enet.h>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <thread>

int new_player_id = 0;

enum class MessageType : uint16_t
{
    CONNECT = 1,  // server assigns clientID
    SET_NAME = 2, // client sets username
};

struct PacketHeader
{
    uint32_t sequence;    // unique sequence number for tracking order/reliablity
    MessageType type;     // type of event/request/response
    uint32_t payloadSize; // size of following payload in bytes
};

struct Packet
{
    PacketHeader header;
    std::vector<uint8_t> payload;
};

// Client's message class
class ClientData
{
private:
    int m_id;
    std::string m_username;

public:
    ClientData(int id) : m_id(id) {}
    void SetUsername(std::string username) { m_username = username; }

    int GetID() { return m_id; }
    std::string GetUsername() { return m_username; }
};
// Map to store client data package and its ID
std::map<int, ClientData *> client_map;
// Broadcast message to all the clients connecting
void BroadcastPacket(ENetHost *server, const char *data)
{
    ENetPacket *packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(server, 0, packet);
}
// Send packet to the client need to receive
// void SendPacket(ENetPeer *peer, const std::vector<uint8_t> &data)
// {
//     ENetPacket *packet = enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_RELIABLE);
//     enet_peer_send(peer, 0, packet);
// }

void SendPacket(ENetPeer *peer, const char *data)
{
    ENetPacket *packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

void ParseData(ENetHost *server, int id, char *data)
{
    // std::cout << "PARSE: " << data << "\n";

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
        BroadcastPacket(server, send_data);
        break;
    }
    case 2: // send id to the client
    {
        char username[80];
        sscanf(data, "2|%[^\n]", &username); // take the username

        char send_data[1024] = {'\0'};
        sprintf(send_data, "2|%d|%s", id, username); // pass the id and username to the data need to send
        // std::cout << "SEND: " << send_data << "\n";

        BroadcastPacket(server, send_data);    // send to all the clients
        client_map[id]->SetUsername(username); // set the client's name of the map managed
        break;
    }
    }
}

/*
void ListenEvent(ENetHost* server, ThreadSafeQueue<ServerEvent>& eventQueue)
{
    while (true) {
        ENetEvent event;
        while (enet_host_service(server, &event, 1000) > 0) {
            ServerEvent ev;
            ev.peer = event.peer;

            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    ev.type = ServerEventType::CONNECT;
                    break;

                case ENET_EVENT_TYPE_RECEIVE: {
                    ev.type = ServerEventType::RECEIVE;

                    // Deserialize raw bytes into PacketHeader + payload
                    PacketHeader header;
                    memcpy(&header, event.packet->data, sizeof(PacketHeader));

                    ev.packet.header = header;
                    ev.packet.payload.resize(header.payloadSize);
                    memcpy(ev.packet.payload.data(),
                           event.packet->data + sizeof(PacketHeader),
                           header.payloadSize);

                    enet_packet_destroy(event.packet); // free ENet’s packet
                    break;
                }

                case ENET_EVENT_TYPE_DISCONNECT:
                    ev.type = ServerEventType::DISCONNECT;
                    break;
            }

            eventQueue.Push(ev);
        }
    }
}
*/
void ListenEvent(ENetHost *server)
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
                printf("A new client connected from %x:%u.\n",
                       event.peer->address.host,
                       event.peer->address.port);
                // for(auto const& x : client_map)
                // {
                //     char send_data[1024] = {'\0'};
                //     sprintf(send_data, "2|%d|%s", x.first, x.second->GetUsername().c_str());
                //     BroadcastPacket(server, send_data); //send the information of connected clients to all the clients
                // }
                // new_player_id++; //each time a new client is connected, ID increments
                // client_map[new_player_id] = new ClientData(new_player_id); //create new client and stores in map
                // event.peer->data = client_map[new_player_id]; //attach client info directly to ENet's peer object

                // PacketHeader header;
                // header.sequence = 0;
                // header.type = MessageType::CONNECT;
                // header.payloadSize = sizeof(new_player_id);

                // std::vector<uint8_t> payload (header.payloadSize);
                // memcpy(payload.data(), &new_player_id, sizeof(new_player_id));

                // Packet response {header, payload};

                // std::vector<uint8_t> buffer(sizeof(PacketHeader) + payload.size());
                // memcpy(buffer.data(), &header, sizeof(PacketHeader));
                // memcpy(buffer.data() + sizeof(PacketHeader), payload.data(), payload.size());

                // // char data_to_send[126] = {'\0'};
                // // sprintf(data_to_send, "3|%d", new_player_id); //pass the ID to the data need to send to the client
                // SendPacket(event.peer, buffer);
                new_player_id++;                                           // each time a new client is connected, ID increments
                client_map[new_player_id] = new ClientData(new_player_id); // create new client and stores in map
                event.peer->data = client_map[new_player_id];

                char data_to_send[126] = {'\0'};
                sprintf(data_to_send, "3|%d", new_player_id); // pass the ID to the data need to send to the client
                SendPacket(event.peer, data_to_send);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                // printf("A packet of length %u containing %s was received from %u on channel %u.\n",
                //         event.packet->dataLength,
                //         event.packet->data,
                //         event.peer->address.port,
                //         event.channelID);

                // ParseData(server, static_cast<ClientData*>(event.peer->data)->GetID(), event.packet->data);
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
            {
                printf("%x:%u disconnected.\n",
                       event.peer->address.host,
                       event.peer->address.port);
                /* Reset the peer's client information. */
                char disconnected_data[126] = {'\0'};
                sprintf(disconnected_data, "4|%d", static_cast<ClientData *>(event.peer->data)->GetID());
                BroadcastPacket(server, disconnected_data);

                event.peer->data = NULL;
                break;
            }
            }
        }
    }
}

void ProcessEvents()
{
    // While there are events in the queue this tick
    // Pop the next event
    // Switch on event type
    // -> Update the client state
    // -> Create a response message
    // -> Send or broadcast the response using SendPacket/BroadCast
    // EndLoop
    /*
    ServerEvent ev;
    while (eventQueue.TryPop(ev)) {  // non-blocking pop
        switch (ev.type) {
            case ServerEventType::CONNECT:
                // Assign new player ID, attach ClientData to ev.peer
                break;

            case ServerEventType::RECEIVE:
                // Parse ev.data into PacketHeader + payload
                // Handle request (SET_USERNAME, TOGGLE_READY, etc.)
                break;

            case ServerEventType::DISCONNECT:
                // Remove client from client_map, broadcast disconnect
                break;
        }
    }
    */
}

void UpdateGame()
{
    // If the game hasn't started
    // Check if all clients are ready
    // If yes -> set gameStarted = true and broadcast GAME_START

    // If the game is running
    // For each player
    // Integrate movement
    // Run physics/collisions/timers if needed
    // After updating the world state
    // Build a snapshot message (World state or just changed entities)
    // Broadcast snapshot to all clients
}

int main(int argc, char **argv)
{
    // Initializes the ENet library (set up sockets, OS, networking stuff)
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occured while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    // Registers enet_deinitialization to be called automatically when the program exits.
    atexit(enet_deinitialize);

    ENetAddress address; // holds IP address and port.
    ENetHost *server;    // represents the server instance.
    ENetEvent event;     // used to handle events (connections, packets, disconnects).

    address.host = ENET_HOST_ANY; // listen on all available network interfaces
    address.port = 7777;          // server's listening port (clients must connect to this port)

    /*
    creates the actual server host. Params:
    - &address -> bind to 0.0.0.0:7777
    - 32 -> maximum number of clients that can connect
    - 1 -> number of channels per connection (like TCP streams inside the ENet)
    - 0 -> incoming bandwidth (0 = unlimited)
    - 0 -> outgoing bandwidth (0 = unlimited)
    */
    server = enet_host_create(&address, 32, 1, 0, 0);

    if (server == NULL)
    {
        fprintf(stderr, "An error occured while trying to create an ENet server host!\n");
        return EXIT_FAILURE;
    }

    // Create thread to listen to incoming events
    std::thread thread(ListenEvent, server);

    // GAME LOOP START
    std::cout << "Update logic for clients\n";
    while (true)
    {
        // server uses fixed time steps
        // ProcessEvents() -> consumes requests -> update states
        // UpdateGame()  -> physics, timers, AI, rules
        // BroadcastUpdates() -> send state back to clients
        // SleepUntilNextTick()
    }
    thread.join();

    // GAME LOOP END
    enet_host_destroy(server);

    return EXIT_SUCCESS;
}