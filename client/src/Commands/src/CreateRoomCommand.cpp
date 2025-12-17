#include "../include/CreateRoomCommand.h"
#include "../../Network/include/NetworkManager.h"
#include "../../Core/include/EventBus.h"
#include <iostream>

void CreateRoomCommand::Execute()
{
	LOG_INFO("Dang tao phong ...");
	NetworkManager::GetInstance().SendRequest(RequestType::CREATE_ROOM);
}
