#include "LobbyState.h"

LobbyState::LobbyState(const std::string &room)
{
    this->m_room = "Room: " + room;
}

void LobbyState::Enter(StateManager& manager)
{
    std::cout << "[LobbyState] Enter\n";
}

void LobbyState::Update(StateManager& manager)
{
    
}

void LobbyState::Draw(StateManager& manager)
{
    DrawText(m_room.c_str(), 10, 10, 20, DARKGREEN);
}

void LobbyState::Exit(StateManager& manager)
{
    std::cout << "[LobbyState] Exit\n";
}
