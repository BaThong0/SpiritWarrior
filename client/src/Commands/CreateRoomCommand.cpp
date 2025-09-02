#include "CreateRoomCommand.h"
#include "../Network/NetworkManager.h"
#include "../Core/EventBus.h"
#include <iostream>

void CreateRoomCommand::Execute()
{
	std::cout << "Dang tao phong ..." << std::endl;
	NetworkManager::GetInstance().SendRequest("CREATE_ROOM", [](bool success) {
		EventBus::GetInstance().Post([success]() {
			if (success) {
				// Xử lý khi tạo phòng thành công
				// Ví dụ: chuyển sang GameRoomState
				std::cout << "Tao phong thanh cong!" << std::endl;
			}
			else {
				// Hiển thị thông báo thất bại
				std::cout << "Tao phong that bai!" << std::endl;
			}
			});
		});
}
