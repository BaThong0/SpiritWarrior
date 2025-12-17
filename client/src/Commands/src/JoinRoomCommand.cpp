#include "../include/JoinRoomCommand.h"
#include "../../Network/include/NetworkManager.h"
#include "../../Core/include/EventBus.h"
#include <iostream>

void JoinRoomCommand::Execute()
{
	LOG_INFO("Dang vao phong ...");
	NetworkManager::GetInstance().SendRequest(RequestType::JOIN_ROOM);
}
