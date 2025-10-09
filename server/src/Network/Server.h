#pragma once

#include <iostream>
#include <thread>
#include <nlohmann/json.hpp>
#include <enet/enet.h>

class Server
{
    int nextPlayerId = 0;
    ENetAddress address; // holds IP address and port.
    ENetHost *server;    // represents the server instance.
    ENetEvent event;     // used to handle events (connections, packets, disconnects).

    std::thread m_workerListenEvent;

    void ListenEvent();
    void BroadcastPacket(const char *data); 
    void ParseData(int id, char *data);
    void HandleConnect(ENetPeer* peer);
    void HandleReceive(ENetPeer* peer, ENetPacket* packet);
public:
    Server();
    ~Server();
    void Run();
};