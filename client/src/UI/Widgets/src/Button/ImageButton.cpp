#include"../../include/Button/ImageButton.h"

ImageButton::ImageButton(const char* image, Vector2 pos, float scale)
{
    Image img = LoadImage(image);
    float newWidth = img.width * scale;
    float newHeight = img.height * scale;
    ImageResize(&img, newWidth, newHeight);
    backGround = LoadTextureFromImage(img);
    UnloadImage(img); // Free image memory after loading texture cause we already have texture in GPU after LoadTextureFromImage
    position = pos;
    bounds = {pos.x, pos.y, newWidth, newHeight};
}

void ImageButton::Update()
{
    
}

void ImageButton::Draw() 
{
    DrawTextureV(backGround, position, WHITE);
}

bool ImageButton::IsPressed()
{
    Vector2 mouse = GetMousePosition();
    m_isPressed = CheckCollisionPointRec(mouse, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    return m_isPressed;
}

bool ImageButton::IsHovered()
{
    Vector2 mouse = GetMousePosition();
    m_isHovered = CheckCollisionPointRec(mouse, bounds);
    return m_isHovered;
}
