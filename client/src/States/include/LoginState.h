#pragma once
#include "IState.h"
#include "../../Core/include/StateManager.h"
#include "../../Core/include/UserManager.h"
#include <string>
#include "Models/Common.h"

class LoginState : public IState
{
private:
    char input[32] = "";
    Rectangle textbox = {300, 200, 200, 40};
    bool mouseOnText = false;

public:
    void Enter(StateManager& manager) override;
    void Update(StateManager& manager) override;
    void Draw(StateManager& manager) override;
    void Exit(StateManager& manager) override;
};