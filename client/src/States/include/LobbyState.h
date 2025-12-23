#pragma once
#include "IState.h"
#include "../../Core/include/StateManager.h"
#include "InGameState.h"
#include"../../UI/Widgets/include/Button.h"
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
    std::string m_room = "0";
    bool isCharacterSelectOpen{false};
    Button characterButton{
        ButtonType::TextButton,
        {20, 100, 220, 50},
        DARKGRAY,
        GRAY,
        "Choose Character", BLACK
    };
    Button startGameButton {
        ButtonType::TextButton,
        {300, 200, 200, 50},
        SKYBLUE,
        DARKBLUE,
        "Start game", BLACK
    };
};