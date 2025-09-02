#include "LoginState.h"
#include "MainMenuState.h"
#include "../Core/StateManager.h"
#include <raylib.h>
#include <cstring>

void LoginState::Update(StateManager &manager)
{
    mouseOnText = CheckCollisionPointRec(GetMousePosition(), textbox);

    if (mouseOnText)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            int len = strlen(input);
            if (key >= 32 && key <= 125 && len < 31)
            {
                input[len] = (char)key;
                input[len + 1] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
        {
            int len = strlen(input);
            if (len > 0)
                input[len - 1] = '\0';
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (strlen(input) > 0) {
            UserManager::Instance().SetUsername(input);
            manager.SetState(new MainMenuState());
        }
    }
}

void LoginState::Draw()
{
    DrawText("Nhap ten nguoi choi:", 300, 150, 20, DARKGRAY);
    DrawRectangleRec(textbox, LIGHTGRAY);
    DrawText(input, (int)textbox.x + 5, (int)textbox.y + 8, 20, BLACK);
    if (mouseOnText) DrawText("Nhap ten va Enter de xac nhan", 300, 250, 18, GRAY);
}
