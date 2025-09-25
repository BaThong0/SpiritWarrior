#include "LobbyState.h"

void LobbyState::SetRoomId(const std::string &room)
{
    this->m_room = "Room: " + room;
}

void LobbyState::Update()
{
    
}

void LobbyState::Draw()
{
    DrawText(m_room.c_str(), 10, 10, 20, DARKGREEN);
}
