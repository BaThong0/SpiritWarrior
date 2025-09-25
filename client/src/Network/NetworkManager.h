#pragma once
#include <functional>
#include <string>
#include <enet/enet.h>
#include <nlohmann/json.hpp>
#include "Models/Common.h"
#include "../Core/UserManager.h"

class NetworkManager
{
public:
	static NetworkManager &GetInstance();
	void SendRequest(const RequestType type);
	void GetMessagesFromServerLoop();
	void SendData();

private:
	NetworkManager();
	NetworkManager(const NetworkManager &) = delete;
	NetworkManager &operator=(const NetworkManager &) = delete;
	ENetHost *client;
	ENetPeer *peer;
	void ParseData(unsigned char *data);
};