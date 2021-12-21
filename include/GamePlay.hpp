#pragma once

#include <memory>
#include <array>
#include <vector>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Ball.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_spikes;
    // sf::Sprite m_sky;
    std::array<sf::Sprite, 3> m_walls;
    sf::Vector2f m_ballDirection;
    sf::Time m_elapsedTime;
    Ball ball;
    // Below is the sufaces
    sf::Time spawnTime;
    std::vector<sf::Sprite> n_surfaces;

    sf::Text m_scoreText;
    int m_score;

public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
    // Function for surfaces
    void SpawnSurfaces();
    // Utility function to generator random number
    int generateRandom();
    // Function to delete the surface tiles when they reaches top
    bool DeleteSurfaces();
};