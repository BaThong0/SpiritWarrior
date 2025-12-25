#include "../include/CharacterSelectorDialog.h"

int CharacterSelectorDialog::selectedCharacter = -1;

void CharacterSelectorDialog::Update() 
{

}
void CharacterSelectorDialog::LoadTexTure()
{
    for (int i = 0; i < (int)CharacterType::Count; i++)
    {
        ImageIcon icon(gCharacters[i].image, {320.0f, 230.0f + i * 70.0f}, 0.1f);
        m_listCharactor.push_back(icon);
    }
}

void CharacterSelectorDialog::Draw()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                  Fade(BLACK, 0.6f));

    DrawText("Select Your Character", 280, 150, 30, WHITE);

    for (int i = 0; i < m_listCharactor.size(); i++)
    {
        m_listCharactor[i].Draw();
    }
    
    DrawText("ENTER: Confirm   ESC: Cancel",
             260, 470, 16, LIGHTGRAY);
}
