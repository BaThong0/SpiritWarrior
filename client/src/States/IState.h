#pragma once
#include <raylib.h>

class StateManager;

class IState
{
public:
    virtual ~IState() = default;
    virtual void Update(StateManager& manager) = 0;
    virtual void Draw() = 0;
};