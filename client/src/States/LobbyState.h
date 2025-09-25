#pragma once
#include "IState.h"
#include "../Core/StateManager.h"

class LobbyState : public IState
{
public:
    void SetRoomId(const std::string &room);
    void Update() override;
    void Draw() override;

private:
    StateManager &manager = StateManager::GetInstance();
    std::string m_room = "0";
};