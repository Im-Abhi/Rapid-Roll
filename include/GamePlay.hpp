#pragma once

#include <memory>
#include <array>

#include <SFML\Graphics\Sprite.hpp>

#include "Game.hpp"
#include "State.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_surface;
    sf::Sprite m_spikes;
    sf::Sprite m_ball;
    // sf::Sprite m_sky;
    std::array<sf::Sprite, 3> m_walls;

public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
};