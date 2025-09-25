#include "CreateRoomCommand.h"
#include "../Network/NetworkManager.h"
#include "../Core/EventBus.h"
#include <iostream>

void CreateRoomCommand::Execute()
{
	std::cout << "Dang tao phong ..." << std::endl;
	NetworkManager::GetInstance().SendRequest(RequestType::CREATE_ROOM);
}
