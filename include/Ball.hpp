#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

#include <windows.h>
#include <vector>

class Ball : public sf::Drawable
{
private:
    sf::Sprite m_ball;
public:
    Ball();
    ~Ball();

    void Init(const sf::Texture &texture);
    void Move(const sf::Vector2f &direction);
    bool isOn(const sf::Sprite &other) const;
    void StartDownward(const sf::Vector2f &speed);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    // Function to check collision with surface tiles
    void checkSurfaceCollision(std::vector<sf::Sprite> &n_surfaces);
};