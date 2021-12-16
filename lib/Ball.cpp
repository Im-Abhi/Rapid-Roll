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
    m_ball.setPosition(250.f,50.f);
    m_ball.setScale(2.f,2.f);
}

void Ball::Move(const sf::Vector2f &direction)
{
    int x_b = m_ball.getPosition().x + direction.x;
    int y_b = m_ball.getPosition().y + direction.y;
    // for collision detection with side walls
    if( x_b == 30 || x_b == 578)
    {
        return;
    }
    m_ball.setPosition(m_ball.getPosition() + direction);
}

bool Ball::isOn(float window_y) const
{
    int y = m_ball.getPosition().y;
    if( y <=40 || y >= window_y -32 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_ball);
}

// Set the ball movement downwards when the game starts
void Ball::StartDownward(const sf::Vector2f &speed)
{
    m_ball.move(speed);
}

void Ball::checkSurfaceCollision(std::vector<sf::Sprite> &n_surfaces)
{
    for(auto surface: n_surfaces)
    {
        if(m_ball.getGlobalBounds().intersects(surface.getGlobalBounds()))
        {
            m_ball.setPosition(m_ball.getPosition().x,surface.getPosition().y-32);
        }
        else
        {
            m_ball.setPosition(m_ball.getPosition().x,m_ball.getPosition().y+0.15f);
        }
    }
}