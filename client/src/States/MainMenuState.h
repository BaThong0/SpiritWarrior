#pragma once
#include "IState.h"
#include "../Core/StateManager.h"

class MainMenuState : public IState
{
public:
    void Enter(StateManager& manager) override;
    void Update(StateManager& manager) override;
    void Draw(StateManager& manager) override;
    void Exit(StateManager& manager) override;
};