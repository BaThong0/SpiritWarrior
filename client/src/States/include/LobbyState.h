#pragma once
#include "IState.h"
#include "../../Core/include/StateManager.h"
#include "InGameState.h"
class LobbyState : public IState
{
public:
    LobbyState(const std::string &room);
    void Enter(StateManager& manager) override;
    void Update(StateManager& manager) override;
    void Draw(StateManager& manager) override;
    void Exit(StateManager& manager) override;

private:
    std::string m_room = "0";
};