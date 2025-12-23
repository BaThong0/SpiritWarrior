#include "../include/CharacterSelectorDialog.h"
#include"../../Widgets/include/Icon.h"
#include "CharacterSelectorDialog.h"
int CharacterSelectorDialog::selectedCharacter = -1;

CharacterSelectorDialog::CharacterSelectorDialog()
{
    
}
void CharacterSelectorDialog::Update() 
{
    
}
void CharacterSelectorDialog::LoadTexTure()
{
    for (int i = 0; i < (int)CharacterType::Count; i++)
    {
        Icon icon(gCharacters[i].image, {320.0f, 230.0f + i * 70.0f}, 0.1f);
        m_listTextures.push_back(icon);
    }
}

void CharacterSelectorDialog::Draw()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                  Fade(BLACK, 0.6f));

    DrawText("Select Your Character", 280, 150, 30, WHITE);

    for (int i = 0; i < (int)CharacterType::Count; i++)
    {
        icon.Draw();
    }
    
    DrawText("ENTER: Confirm   ESC: Cancel",
             260, 470, 16, LIGHTGRAY);
}
