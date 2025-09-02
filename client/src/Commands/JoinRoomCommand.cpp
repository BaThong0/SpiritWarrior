#include "JoinRoomCommand.h"
#include "../Network/NetworkManager.h"
#include "../Core/EventBus.h"
#include <iostream>

void JoinRoomCommand::Execute()
{
	std::cout << "Dang vao phong ..." << std::endl;
	NetworkManager::GetInstance().SendRequest("JOIN_ROOM", [](bool success) {
		EventBus::GetInstance().Post([success]() {
			if (success) {
				// Vào phòng thành công
				// Chuyển sang trạng thái GameRoomState
				std::cout << "Vao phong thanh cong!" << std::endl;
			}
			else {
				// Hiển thị lỗi
				std::cout << "Vao phong that bai!" << std::endl;
			}
			});
		});
}
