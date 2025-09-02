#include "NetworkManager.h"
#include <thread>

NetworkManager& NetworkManager::GetInstance()
{
	static NetworkManager instance;
	return instance;
}

void NetworkManager::SendRequest(const std::string& type, Callback cb)
{
	// Giả lập: gửi lên server (có thể chạy thread riêng)
	// Sau 2 giây trả kết quả
	std::thread([cb]() {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		bool result = true;
		cb(result);
		}).detach();
}
