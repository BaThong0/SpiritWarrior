#include "NetworkManager.h"
#include "../Core/EventBus.h"
#include <thread>
#include <iostream>
#include "../../include/logger.h"
using json = nlohmann::json;

NetworkManager::NetworkManager()
{
  std::thread(&NetworkManager::GetMessagesFromServerLoop, this).detach();
}

void NetworkManager::ParseData(unsigned char *data)
{
  int data_type;
  int id;
  const char *dataStr = reinterpret_cast<const char *>(data);
  sscanf(dataStr, "%d|%d", &data_type, &id);
  switch (data_type)
  {
  case 3:
    LOG_INFO("ID: %d", id);
    break;
  }
}

NetworkManager &NetworkManager::GetInstance()
{
  static NetworkManager instance;
  return instance;
}

void NetworkManager::SendRequest(const RequestType type)
{
  LOG_INFO("Request type before thread: %d", static_cast<int>(type));
  std::thread( //Khong nen truyen reference vao
      [this, type]()
      {
        LOG_INFO("Send Request called");
        // Giả lập: gửi lên server (có thể chạy thread riêng)
        // Sau 2 giây trả kết quả
        json message;
        LOG_INFO("Request type: %d", static_cast<int>(type));
        switch (type)
        {
        case RequestType::CREATE_ROOM:
        {
          UserInfo userInfo{UserManager::Instance().GetUserID(), UserManager::Instance().GetRoomID(), UserManager::Instance().GetUsername()};
          message["type"] = "CREATE_ROOM";
          message["data"] = {
              {"room_name", "BattleArena"},
              {"max_players", 8},
              {"mode", "deathmatch"}};
          message["meta"] = {
              {"request_id", "abc123"},
              {"timestamp", time(nullptr)}};
          break;
        }
        case RequestType::START_GAME:
        {
          UserInfo userInfo{UserManager::Instance().GetUserID(), UserManager::Instance().GetRoomID(), UserManager::Instance().GetUsername()};
          message["type"] = "START_GAME";
          message["data"] = {
            {"room_id", UserManager::Instance().GetRoomID()}
          };
          break;
        }
        default:
          LOG_DEBUG("Wrong type try again!\n");
        }
        std::string msgStr = message.dump();

        ENetPacket *packet = enet_packet_create(
            msgStr.c_str(),
            msgStr.size() + 1,
            ENET_PACKET_FLAG_RELIABLE);

        enet_peer_send(peer, 0, packet);
      })
      .detach();
}

void NetworkManager::SendData()
{
  // Build JSON
  json message;
  message["type"] = "player_update";
  message["id"] = 1;
  message["position"] = {{"x", 100}, {"y", 200}};
  message["health"] = 95;

  // Convert to string
  std::string msgStr = message.dump();

  // Create ENet packet
  ENetPacket *packet = enet_packet_create(
      msgStr.c_str(),
      msgStr.size() + 1, // include null terminator if you want
      ENET_PACKET_FLAG_RELIABLE);

  // Send to peer (channel 0)
  enet_peer_send(peer, 0, packet);
}

void NetworkManager::GetMessagesFromServerLoop()
{
  if (enet_initialize() != 0)
  {
    fprintf(stderr, "An error occured while initializing Enet!\n");
    return;
  }
  atexit(enet_deinitialize);

  client = enet_host_create(NULL, 1, 1, 0, 0);

  if (client == NULL)
  {
    fprintf(stderr, "An error occured while trying to create an ENet client host !\n");
    return;
  }

  ENetAddress address;
  ENetEvent event;
  // ENetPeer *peer;

  enet_address_set_host(&address, "127.0.0.1");
  address.port = 7777;

  peer = enet_host_connect(client, &address, 1, 0);
  if (peer == NULL)
  {
    fprintf(stderr, "No available peers for initiating an ENet connection\n");
    return;
  }

  if (enet_host_service(client, &event, 5000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT)
  {
    LOG_INFO("Connection to 127.0.0.1:7777 succeeded.");
  }
  else
  {
    enet_peer_reset(peer);
    LOG_INFO("Connection to 127.0.0.1:7777 failed.");
    return;
  }

  while (true)
  {
    ENetEvent event;
    while (enet_host_service(client, &event, 1000) > 0)
    {
      switch (event.type)
      {
      case ENET_EVENT_TYPE_RECEIVE:
        // printf("A packet of length %u containing %s was received from %s on channel %u.\n",
        // event.packet->dataLength,
        // event.packet->data,
        // event.peer->data,
        // event.channelID);
        // ParseData(event.packet->data);
        // SendData();
        std::string data(reinterpret_cast<char *>(event.packet->data));

        try
        {
          auto j = json::parse(data);
          std::string type = j["type"];
          std::string status = j["status"];
          if (type == "INITIALIZE_ID")
          {
            std::cout << j["data"]["client_id"] << "\n";
            UserManager::Instance().SetUserID(j["data"]["client_id"].get<int>());
            LOG_INFO("Assigned Client ID: %d\n", UserManager::Instance().GetUserID());
          }
          else if (type == "CREATE_ROOM_RESPONSE")
          {
            if (status == "success")
            {
              int room_ID = j["data"]["room_id"].get<int>();
              UserManager::Instance().SetRoomID(room_ID);
              EventBus::GetInstance().Publish("CreateRoomSuccessful", std::to_string(room_ID));
              //
            }
            else
            {
              std::string error = j["error"];
              LOG_INFO("Failed to create room:%s\n", error);
            }
          }
        }
        catch (std::exception &e)
        {
          std::cerr << "Response parse error: " << e.what() << "\n";
        }
        enet_packet_destroy(event.packet);

        break;
      }
    }
  }
}
