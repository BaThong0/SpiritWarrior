#include "InGameState.h"

void InGameState::Enter(StateManager &manager)
{
    LOG_INFO("[InGameState] Enter\n");
    EventBus::GetInstance().Subsribe("UpdatePosition", [&manager](const std::string &data)
    {
        
    });
    m_player_info.X = 100; 
    m_player_info.Y = 100;
    m_player_info.name = UserManager::Instance().GetUsername();
}

void InGameState::Update(StateManager &manager)
{
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) m_player_info.X++;
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) m_player_info.X--;
    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) m_player_info.Y--;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) m_player_info.Y++;

    NetworkManager::GetInstance().SendData(m_player_info.X, m_player_info.Y);
}

void InGameState::Draw(StateManager &manager)
{
    DrawRectangle(m_player_info.X, m_player_info.Y, 50, 50, ORANGE);
    DrawText(m_player_info.name.c_str(), 340, 285, 20, BLACK);
}

void InGameState::Exit(StateManager &manager)
{
}
