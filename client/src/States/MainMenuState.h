#pragma once
#include "IState.h"

class MainMenuState : public IState
{
public:
    void Update(StateManager &manager) override;
    void Draw() override;
};