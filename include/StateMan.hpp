#pragma once

#include <stack>
#include <memory>

#include <State.hpp>

namespace Engine
{
class StateMan
{
private:
    // This creates a state stack which will hold all the states while game is running
    std::stack<std::unique_ptr<State>> m_stateStack;

    // This will be used to add new state to the stack only when the previous state is completed
    std::unique_ptr<State> m_newState;

    bool m_add;
    bool m_replace;
    bool m_remove;

public:
    StateMan();
    ~StateMan();

    // This method is used to push the new state to the state stack
    void Add(std::unique_ptr<State> toAdd, bool replace = false);

    // This method will pop or remove the top state from the state stack
    void PopCurrent();

    // In this mehtod actual process will take place like push and pop
    void ProcessStateChange();

    // This will be used to get the current game state from the state stack
    std::unique_ptr<State>& GetCurrent();
};

} // namespace Engine
