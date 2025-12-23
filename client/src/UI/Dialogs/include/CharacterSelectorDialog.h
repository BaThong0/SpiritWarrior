#pragma once
#include"IDialog.h"
#include<raylib.h>
#include<vector>
#include"../../UI/Widgets/include/Icon.h"
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

    void Open() override
    {
        m_isOpen = true;
    }
    void Close() override
    {
        m_isOpen = false;
    }
    
    static void LoadTexTure();
    static void Update();
    static void Draw();
private:
static std::vector<Icon> m_listTextures;
};  