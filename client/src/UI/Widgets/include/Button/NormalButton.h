#pragma once
#include <raylib.h>
#include <iostream>
#include"IButton.h"
class NormalButton : public IButton
{
    public:
    NormalButton() = default;
    NormalButton(Rectangle rect, Color normal, Color hover, const char* txt, Color textColor = BLACK)
        : bounds(rect), normalColor(normal), hoverColor(hover), text(txt), textColor(textColor) {} //Contructor for text
    ~NormalButton() = default;

    void Update() override;
    void Draw() override;
    bool IsPressed() override;
    bool IsHovered() override;

    private:
    //for text button
    Rectangle bounds;
    const char* text;
    Color normalColor;
    Color hoverColor;
    Color textColor = BLACK;
};