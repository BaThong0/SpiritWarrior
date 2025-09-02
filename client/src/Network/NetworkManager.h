#pragma once
#include <functional>
#include <string>

class NetworkManager {
public:
	using Callback = std::function<void(bool)>;
	static NetworkManager& GetInstance();
	void SendRequest(const std::string& type, Callback cb);
private:
	NetworkManager() = default;
	NetworkManager(const NetworkManager&) = delete;
	NetworkManager& operator=(const NetworkManager&) = delete;
};