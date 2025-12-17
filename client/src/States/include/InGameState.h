#pragma once
#include "IState.h"
#include "../../Core/include/StateManager.h"
#include "../../../include/logger.h"
#include "../../Core/include/EventBus.h"
#include "../../Core/include/UserManager.h"
#include "../../Network/include/NetworkManager.h"
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