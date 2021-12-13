#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context>& context) 
    :   m_context(context), 
        m_elapsedTime(sf::Time::Zero)
{

}

GamePlay::~GamePlay() 
{

}

void GamePlay::Init()
{
    // change the line below for the background in future
    // m_context->m_assets->AddTexture(SKY,"assets/sky.png", true);
    m_context->m_assets->AddTexture(WALL,"assets\\textures\\wall.png", true);
    m_context->m_assets->AddTexture(SPIKE,"assets\\textures\\spike.png", true);
    m_context->m_assets->AddTexture(SURFACE,"assets\\textures\\surface.png");
    m_context->m_assets->AddTexture(BALL,"assets\\textures\\ball.png");

    // m_sky.setTexture(m_context->m_assets->GetTexture(SKY));
    // m_sky.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for(auto &wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }
    m_walls[0].setTextureRect(sf::IntRect(0, 0 ,m_context->m_window->getSize().x, 16));  // Top wall

    m_walls[1].setTextureRect(sf::IntRect(0, 0 ,32 ,m_context->m_window->getSize().y));  // Left wall

    m_walls[2].setTextureRect(sf::IntRect(0, 0 ,32, m_context->m_window->getSize().y));  // Right wall
    m_walls[2].setPosition(m_context->m_window->getSize().x-32,0);
    m_spikes.setTexture(m_context->m_assets->GetTexture(SPIKE));
    m_spikes.setTextureRect(sf::IntRect(0,0,m_context->m_window->getSize().x,16));
    m_spikes.setScale(1.f,2.f);
    m_spikes.setPosition(0,16);

    ball.Init(m_context->m_assets->GetTexture(BALL));
}
void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::A:
                m_ballDirection = {-2.f,0.f};
                ball.Move(m_ballDirection);
                break;
            case sf::Keyboard::D:
                m_ballDirection = {2.f,0.f};
                ball.Move(m_ballDirection);
                break;
            case sf::Keyboard::S:
                m_ballDirection = {0.f,2.f};
                ball.Move(m_ballDirection);
                break;
            default:
                break;
            }
        }
    }
}
void GamePlay::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime.asSeconds() > 0.1)
    {
        m_elapsedTime = sf::Time::Zero;
    }
}
void GamePlay::Draw()
{
    m_context->m_window->clear(sf::Color::Cyan);
    m_context->m_window->draw(m_spikes);
    ball.StartDownward({0.f, 0.4f});
    m_context->m_window->draw(ball);
    for(auto &wall: m_walls)
    {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->display();
}
void GamePlay::Pause()
{

}
void GamePlay::Start()
{

}