#pragma once
#include <functional>
#include <string>
#include <enet/enet.h>
#include <nlohmann/json.hpp>
#include "Models/Common.h"
#include "../../Core/include/UserManager.h"
#include "../../include/logger.h"
class NetworkManager
{
public:
	static NetworkManager &GetInstance();
	void SendRequest(const RequestType type, nlohmann::json j = {});
	void GetMessagesFromServerLoop();
	void SendData(int, int);

private:
	NetworkManager();
	NetworkManager(const NetworkManager &) = delete;
	NetworkManager &operator=(const NetworkManager &) = delete;
	ENetHost *client;
	ENetPeer *peer;
	void ParseData(unsigned char *data);
};