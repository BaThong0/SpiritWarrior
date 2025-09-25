#include "MainMenuState.h"
#include "LobbyState.h"
#include "../Core/UserManager.h"
#include "../Core/EventBus.h"
#include "../Commands/CreateRoomCommand.h"
#include "../Commands/JoinRoomCommand.h"

MainMenuState::MainMenuState()
{
    EventBus::GetInstance().Subsribe("CreateRoomSuccessful", [this](const std::string &data)
                                     { 
                                        LobbyState* state = new LobbyState();
                                        state->SetRoomId(data);
                                        manager.SetState(state); });
}

void MainMenuState::Update()
{
    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, {300, 200, 200, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        ICommand *cmd = new CreateRoomCommand();
        cmd->Execute();
        delete cmd;
    }

    if (CheckCollisionPointRec(mouse, {300, 270, 200, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        ICommand *cmd = new JoinRoomCommand();
        cmd->Execute();
        delete cmd;
    }
}

void MainMenuState::Draw()
{
    DrawText(("Xin chao, " + UserManager::Instance().GetUsername()).c_str(), 250, 150, 20, DARKGREEN);
    DrawRectangle(300, 200, 200, 50, SKYBLUE);
    DrawText("Tao phong", 340, 215, 20, BLACK);
    DrawRectangle(300, 270, 200, 50, ORANGE);
    DrawText("Vao phong", 340, 285, 20, BLACK);
}
