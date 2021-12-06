#pragma once

#include <SFML/System/Time.hpp>

namespace Engine
{
    class State
    {
    public:
        State();
        virtual ~State();
        
        virtual void Init() = 0;    //for setting up the sprites text and thier positions
        virtual void ProcessInput() = 0; // handle keyPress and mouse clicks
        virtual void Update(sf::Time deltaTime) = 0; 
        virtual void Draw() = 0; // For drawing sprites on the game window

        virtual void Pause(){};
        virtual void Start(){};
    };
} // namespace Engine
