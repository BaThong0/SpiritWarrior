#pragma once
#include "IState.h"
#include "../Core/StateManager.h"
#include "../../../include/logger.h"
#include "../Core/EventBus.h"
#include "../Core/UserManager.h"
#include "../Network/NetworkManager.h"
class InGameState : public IState
{
public:
    // InGameState(const std::string &room);
    void Enter(StateManager& manager) override;
    void Update(StateManager& manager) override;
    void Draw(StateManager& manager) override;
    void Exit(StateManager& manager) override;

private:
    PlayerInfo m_player_info;
    MapInfo m_map_info;
};