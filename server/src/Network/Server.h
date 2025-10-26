#pragma once

#include <iostream>
#include <thread>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <enet/enet.h>

class Server
{
    unsigned int nextPlayerId = 0;
    unsigned int nextRoomId = 1000;
    ENetAddress address; // holds IP address and port.
    ENetHost *server;    // represents the server instance.
    ENetEvent event;     // used to handle events (connections, packets, disconnects).

    std::thread m_workerListenEvent;
    std::unordered_map<unsigned int, std::pair<ENetPeer, std::thread>> m_roomList;
    void ListenEvent();
    void BroadcastPacket(const char *data); 
    void ParseData(int id, char *data);
    void HandleConnect(ENetPeer* peer);
    void HandleReceive(ENetPeer* peer, ENetPacket* packet);
    void RoomLoop(unsigned int, ENetPeer*);
public:
    Server();
    ~Server();
    void Run();
};