#pragma once
#include <functional>
#include <string>
#include <enet/enet.h>
enum class RequestType {
    CREATE_ROOM,
    JOIN_ROOM,
    PLAYER_MOVE,
    UNKNOWN
};

class NetworkManager
{
public:
	using Callback = std::function<void(bool)>;
	static NetworkManager &GetInstance();
	void SendRequest(const std::string &type, Callback cb);
	void GetMessagesFromServerLoop();
	void SendData();
private:
	NetworkManager();
	NetworkManager(const NetworkManager &) = delete;
	NetworkManager &operator=(const NetworkManager &) = delete;
	ENetHost *client;
	ENetPeer *peer;
	void ParseData(unsigned char* data);
};