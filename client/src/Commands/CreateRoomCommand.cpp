#include "CreateRoomCommand.h"
#include "../Network/NetworkManager.h"
#include "../Core/EventBus.h"
#include <iostream>

void CreateRoomCommand::Execute()
{
	LOG_INFO("Dang tao phong ...");
	NetworkManager::GetInstance().SendRequest(RequestType::CREATE_ROOM);
}
