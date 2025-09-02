#pragma once
#include "IState.h"
#include "../Core/UserManager.h"
#include <string>

class LoginState : public IState
{
private:
    char input[32] = "";
    Rectangle textbox = {300, 200, 200, 40};
    bool mouseOnText = false;

public:
    void Update(StateManager &manager) override;
    void Draw() override;
};