#include "../include/StartGameCommand.h"
#include "../../Network/include/NetworkManager.h"
#include "../../Core/include/EventBus.h"
#include <iostream>

void StartGameCommand::Execute()
{
	LOG_INFO("Dang vao game ...");
	NetworkManager::GetInstance().SendRequest(RequestType::START_GAME);
}
