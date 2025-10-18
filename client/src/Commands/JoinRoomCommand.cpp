#include "JoinRoomCommand.h"
#include "../Network/NetworkManager.h"
#include "../Core/EventBus.h"
#include <iostream>

void JoinRoomCommand::Execute()
{
	LOG_INFO("Dang vao phong ...");
	NetworkManager::GetInstance().SendRequest(RequestType::JOIN_ROOM);
}
