#include"../../include/Button/NormalButton.h"

void NormalButton::Update()
{
    
}

void NormalButton::Draw() 
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

bool NormalButton::IsPressed()
{
    Vector2 mouse = GetMousePosition();
    m_isPressed = CheckCollisionPointRec(mouse, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    return m_isPressed;
}

bool NormalButton::IsHovered()
{
    Vector2 mouse = GetMousePosition();
    m_isHovered = CheckCollisionPointRec(mouse, bounds);
    return m_isHovered;
}
