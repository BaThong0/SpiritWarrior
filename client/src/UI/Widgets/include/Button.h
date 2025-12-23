#pragma once
#include <raylib.h>
# include <iostream>
enum class ButtonType
{
    ImageButton,
    TextButton
};
class Button
{
    public:
    Button() = default;
    Button(ButtonType buttonType, Rectangle rect, Color normal, Color hover, const char* txt, Color textColor = BLACK)
        : m_buttonType(buttonType), bounds(rect), normalColor(normal), hoverColor(hover), text(txt), textColor(textColor) {} //Contructor for text
    Button(ButtonType buttonType, const char* image, Vector2 pos, float scale);
    ~Button() = default;
    void Update();
    void Draw();
    bool IsPressed();
    bool IsHovered();

    private:
    ButtonType m_buttonType{ButtonType::TextButton};
    //for image button
    Texture2D backGround;
    Vector2 position;
    //for text button
    Rectangle bounds;
    const char* text;
    Color normalColor;
    Color hoverColor;
    Color textColor = BLACK;
    bool m_isPressed = false;
    bool m_isHovered = false;
};