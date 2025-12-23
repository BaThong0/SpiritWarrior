#include"../include/Button.h"
#include "../include/Button.h"
Button::Button(ButtonType buttonType, const char* image, Vector2 pos, float scale)
{
    m_buttonType = buttonType;
    Image img = LoadImage(image);
    int width = static_cast<int>(img.width * scale);
    int height = static_cast<int>(img.height * scale);
    backGround = LoadTextureFromImage(img);
    UnloadImage(img); // Free image memory after loading texture cause we already have texture in GPU after LoadTextureFromImage
    position = pos;
}

void Button::Update()
{
    Vector2 mouse = GetMousePosition();
    m_isHovered = CheckCollisionPointRec(mouse, bounds);
    
}

void Button::Draw() 
{
    if(m_buttonType == ButtonType::TextButton) // No texture loaded
    {
        Color color = m_isHovered ? hoverColor : normalColor;
        int fontSize = 20;
        int textWidth = MeasureText(text, fontSize);
        DrawRectangleRounded(bounds, 0.2f, 10, color);
        DrawText(text,
            bounds.x + (bounds.width - textWidth) / 2,
            bounds.y + (bounds.height - fontSize) / 2,
            fontSize,
            textColor);
    }
    else //texture button
    DrawTextureV(backGround, position, WHITE);
}

bool Button::IsPressed()
{
    Vector2 mouse = GetMousePosition();
    m_isPressed = CheckCollisionPointRec(mouse, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    return m_isPressed;
}

bool Button::IsHovered()
{
    Vector2 mouse = GetMousePosition();
    m_isHovered = CheckCollisionPointRec(mouse, bounds);
    return m_isHovered;
}
