#include "../include/LobbyState.h"
#include "../../Commands/include/StartGameCommand.h"

LobbyState::LobbyState(const std::string &room)
{
    this->m_room = "Room: " + room;
}

void LobbyState::Enter(StateManager& manager)
{
    std::cout << "[LobbyState] Enter\n";
    characterSelectorDialog.LoadTexTure();
}

void LobbyState::Update(StateManager& manager)
{
    Vector2 mouse = GetMousePosition();
    characterButton.Update();
    startGameButton.Update();
    if (characterButton.IsPressed())
    {
        isCharacterSelectOpen = true;
    }

    if (CheckCollisionPointRec(mouse, {300, 200, 200, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        manager.SetState(std::make_unique<InGameState>());
        ICommand *cmd = new StartGameCommand();
        cmd->Execute();
        delete cmd;
    }
}

void LobbyState::Draw(StateManager& manager)
{
    DrawText(m_room.c_str(), 10, 10, 20, DARKGREEN);
    if (isCharacterSelectOpen) // Draw character select dialog first to be on top
    {
        characterSelectorDialog.Draw();
        return;
    }
    characterButton.Draw();
    startGameButton.Draw();
}

void LobbyState::Exit(StateManager& manager)
{
    std::cout << "[LobbyState] Exit\n";
}
