#pragma once
#include <memory>
#include "../States/IState.h"

class StateManager
{
private:
    std::unique_ptr<IState> currentState = nullptr;
public:
    void SetState(std::unique_ptr<IState> state)
    {
        if (currentState) currentState->Exit(*this);
        currentState = std::move(state);
        if (currentState) currentState->Enter(*this);
    }

    void Update()
    {
        if (currentState)
            currentState->Update(*this);
    }

    void Draw()
    {
        if (currentState)
            currentState->Draw(*this);
    }

    ~StateManager()
    {

    }
};