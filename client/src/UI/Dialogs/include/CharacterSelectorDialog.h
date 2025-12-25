#pragma once
#include"IDialog.h"
#include<raylib.h>
#include<vector>
#include"../../Widgets/include/Icon/IIcon.h"
#include"../../Widgets/include/Icon/ImageIcon.h"

enum class CharacterType
{
    Warrior,
    Mage,
    Archer,
    Count
};
struct CharacterInfo
{
    const char* name;
    const char* image;
};

static CharacterInfo gCharacters[] = {
    {"Warrior", "Graphics/warrior.jpg"},
    {"Mage", "Graphics/Mage.png"},
    {"Archer", "Graphics/knight.jpg"}
};

class CharacterSelectorDialog : public IDialog
{
public:
    static int selectedCharacter;
    CharacterSelectorDialog() = default;
    ~CharacterSelectorDialog() = default;

    void LoadTexTure();
    void Update();
    void Draw();
private:
std::vector<ImageIcon> m_listCharactor;
};  