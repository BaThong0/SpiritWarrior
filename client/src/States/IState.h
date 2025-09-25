#pragma once
#include <raylib.h>
#include <iostream>

class IState
{
public:
    virtual ~IState() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};