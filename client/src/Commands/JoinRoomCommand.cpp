#include "JoinRoomCommand.h"
#include "../Network/NetworkManager.h"
#include "../Core/EventBus.h"
#include <iostream>

void JoinRoomCommand::Execute()
{
	std::cout << "Dang vao phong ..." << std::endl;
	NetworkManager::GetInstance().SendRequest(RequestType::JOIN_ROOM);
}
