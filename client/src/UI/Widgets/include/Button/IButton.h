#pragma once
#include <raylib.h>
#include <iostream>

class IButton
{
    public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool IsPressed() = 0;
    virtual bool IsHovered() = 0;
    bool m_isPressed = false;
    bool m_isHovered = false;
};