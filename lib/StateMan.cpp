#include "StateMan.hpp"

Engine::StateMan::StateMan() : m_add(false), m_replace(false), m_remove(false)
{

}

Engine::StateMan::~StateMan() 
{

}

void Engine::StateMan::Add(unique_ptr<State> toAdd, bool replace)
{
    m_add = true;
    m_newState = move(toAdd);

    m_replace = replace;
}

void Engine::StateMan::PopCurrent()
{
    m_remove = true;
}

void Engine::StateMan::ProcessStateChange()
{
    if(m_remove && (!m_stackState.empty()))
    {
        m_stackState.pop();

        if(!m_stackState.empty())
        {
            m_stackState.top()->Start();
        }

        m_remove = false;
    }

    if(m_add)
    {
        if(m_replace && (m_stackState.empty()))
        {
            m_stackState.pop();
            m_replace = false;
        }

        if(!m_stackState.empty())
        {
            m_stackState.top()->Pause();
        }    

        m_stackState.push(move(m_newState));
        m_add = false;
    }
}

unique_ptr<Engine::State> &Engine::StateMan::GetCurrent()
{

}