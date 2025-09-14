#pragma once
#include <functional>
#include <string>
#include <enet/enet.h>

class NetworkManager
{
public:
	using Callback = std::function<void(bool)>;
	static NetworkManager &GetInstance();
	void SendRequest(const std::string &type, Callback cb);
	void GetMessagesFromServerLoop();

private:
	NetworkManager();
	NetworkManager(const NetworkManager &) = delete;
	NetworkManager &operator=(const NetworkManager &) = delete;
	ENetHost *client;
	void ParseData(unsigned char* data);
};