#pragma once
#include "IState.h"
#include "../Core/StateManager.h"
#include "../Core/UserManager.h"
#include <string>
#include "Models/Common.h"

class LoginState : public IState
{
private:
    StateManager &manager = StateManager::GetInstance();
    char input[32] = "";
    Rectangle textbox = {300, 200, 200, 40};
    bool mouseOnText = false;

public:
    void Update() override;
    void Draw() override;
};