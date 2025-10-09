#pragma once
#include <raylib.h>
#include <iostream>

class StateManager;

class IState
{
public:
    virtual ~IState() = default;
    virtual void Enter(StateManager& manager) = 0;
    virtual void Update(StateManager& manager) = 0;
    virtual void Draw(StateManager& manager) = 0;
    virtual void Exit(StateManager& manager) = 0;
};