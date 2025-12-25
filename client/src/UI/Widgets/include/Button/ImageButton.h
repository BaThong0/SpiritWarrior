#pragma once
#include <raylib.h>
#include <iostream>
#include "IButton.h"

class ImageButton : public IButton
{
    public:
    ImageButton() = default;
    ImageButton(const char* image, Vector2 pos, float scale);
    ~ImageButton() = default;
    void Update() override;
    void Draw() override;
    bool IsPressed() override;
    bool IsHovered() override;

    private:
    //for image button
    Texture2D backGround;
    Vector2 position;
    Rectangle bounds;
};