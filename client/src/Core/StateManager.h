#pragma once
#include "../States/IState.h"

class StateManager
{
private:
    IState *currentState = nullptr;

public:
    void SetState(IState *state)
    {
        if (currentState)
            delete currentState;
        currentState = state;
    }

    void Update()
    {
        if (currentState)
            currentState->Update(*this);
    }

    void Draw()
    {
        if (currentState)
            currentState->Draw();
    }

    ~StateManager()
    {
        if (currentState)
            delete currentState;
    }
};