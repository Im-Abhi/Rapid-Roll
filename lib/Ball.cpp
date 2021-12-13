#include "Ball.hpp"

Ball::Ball() 
{

}

Ball::~Ball() 
{

}

void Ball::Init(const sf::Texture &texture)
{
    m_ball.setTexture(texture);
    m_ball.setPosition(50.f,50.f);
    m_ball.setScale(2.f,2.f);
}

void Ball::Move(const sf::Vector2f &direction)
{
    m_ball.setPosition(m_ball.getPosition() + direction);
}

bool Ball::isOn(const sf::Sprite &other) const
{
    
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_ball);
}

void Ball::StartDownward(const sf::Vector2f &speed)
{
    m_ball.move(speed);
}