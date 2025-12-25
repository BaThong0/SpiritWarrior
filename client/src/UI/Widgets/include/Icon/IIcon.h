#pragma once
#include <raylib.h>
class IIcon
{
    public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    private:
    Texture2D texture;
    Vector2 position;
};