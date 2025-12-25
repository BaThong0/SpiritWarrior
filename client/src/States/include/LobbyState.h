#pragma once
#include "IState.h"
#include "../../Core/include/StateManager.h"
#include "InGameState.h"
#include"../../UI/Widgets/include/Button/NormalButton.h"
#include"../../UI/Dialogs/include/CharacterSelectorDialog.h"
class LobbyState : public IState
{
public:
    LobbyState(const std::string &room);
    void Enter(StateManager& manager) override;
    void Update(StateManager& manager) override;
    void Draw(StateManager& manager) override;
    void Exit(StateManager& manager) override;

private:
    CharacterSelectorDialog characterSelectorDialog;
    std::string m_room = "0";
    bool isCharacterSelectOpen{false};
    NormalButton characterButton{
        {20, 100, 220, 50},
        DARKGRAY,
        GRAY,
        "Choose Character", BLACK
    };
    NormalButton startGameButton {
        {300, 200, 200, 50},
        SKYBLUE,
        DARKBLUE,
        "Start game", BLACK
    };
};