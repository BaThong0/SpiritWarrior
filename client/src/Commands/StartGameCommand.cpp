#include "StartGameCommand.h"
#include "../Network/NetworkManager.h"
#include "../Core/EventBus.h"
#include <iostream>

void StartGameCommand::Execute()
{
	LOG_INFO("Dang vao game ...");
	NetworkManager::GetInstance().SendRequest(RequestType::START_GAME);
}
