#pragma once
#include "../States/IState.h"

class StateManager
{
private:
    IState *currentState = nullptr;
    StateManager() = default;
    StateManager(const StateManager&) = delete;
    StateManager(StateManager&&) = delete;
public:
    static StateManager& GetInstance() {
        static StateManager manager;
        return manager;
    }

    void SetState(IState *state)
    {
        if (currentState)
            delete currentState;
        currentState = state;
    }

    void Update()
    {
        if (currentState)
            currentState->Update();
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