#pragma once

#include <SFML/System/Time.hpp>

namespace Engine
{
    class State
    {
    public:
        State(){};
        virtual ~State(){};

        // Initial setup of state like setting up the sprites textures and text
        virtual void Init() = 0;

        // Process any keyboard or mouse input provided by the user
        virtual void ProcessInput() = 0;

        /*         
            This will react to the inputs handled in the processInput method and will make changes in the state.
        */        
        virtual void Update(sf::Time deltaTime) = 0;
        
        // This will draw all the sprites on the render Window
        virtual void Draw() = 0;

        // This method will help us to pause the game
        virtual void Pause(){};

        // This method will help us to resume and play the game
        virtual void Start(){};
    };
    
} // namespace Engine
