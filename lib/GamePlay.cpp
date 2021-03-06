#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context>& context) 
    :   m_context(context), 
        m_elapsedTime(sf::Time::Zero),
        spawnTime(sf::Time::Zero),
        m_score(0),
        m_isPaused(false)
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
    m_walls[0].setColor(sf::Color::Black);
    m_walls[1].setTextureRect(sf::IntRect(0, 0 ,32 ,m_context->m_window->getSize().y));  // Left wall

    m_walls[2].setTextureRect(sf::IntRect(0, 0 ,32, m_context->m_window->getSize().y));  // Right wall
    m_walls[2].setPosition(m_context->m_window->getSize().x-32,0);
    m_spikes.setTexture(m_context->m_assets->GetTexture(SPIKE));
    m_spikes.setTextureRect(sf::IntRect(0,0,m_context->m_window->getSize().x,16));
    m_spikes.setScale(1.f,2.f);
    m_spikes.setPosition(0,16);
    SpawnSurfaces();
    ball.Init(m_context->m_assets->GetTexture(BALL));

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setPosition(32,0);
    m_scoreText.setCharacterSize(15);
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
            case sf::Keyboard::Escape:
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                break;
            default:
                break;
            }
        }
    }
}
void GamePlay::Update(sf::Time deltaTime)
{
    if(m_isPaused)
        return;
    m_elapsedTime += deltaTime;
    ball.checkSurfaceCollision(n_surfaces);
    if (m_elapsedTime.asSeconds() > 0.1)
    {
        if(ball.isOn(m_context->m_window->getSize().y))
        {
            m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
        }
        m_elapsedTime = sf::Time::Zero;
    }
    if(DeleteSurfaces())
    {
        m_score += 1;
        m_scoreText.setString("Score : " + std::to_string(m_score));
    }
    spawnTime += deltaTime;
    if(spawnTime.asSeconds() >= 4.f)
    {
        SpawnSurfaces();
        spawnTime = sf::Time::Zero;
    }
}
void GamePlay::Draw()
{
    m_context->m_window->clear(sf::Color(102,204,255));
    sf::Texture m_bg;
    m_bg.loadFromFile("assets\\textures\\clouds.jpg");
    sf::Sprite bg;
    bg.setTexture(m_bg);
    m_context->m_window->draw(bg);
    m_context->m_window->draw(m_spikes);
    m_context->m_window->draw(ball);
    for(auto &surface: n_surfaces)
    {
        m_context->m_window->draw(surface);
        surface.move(0.f, -0.4f);
    }
    for(auto &wall: m_walls)
    {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->display();
}

void GamePlay::Pause()
{
    m_isPaused = true;
}
void GamePlay::Start()
{
    m_isPaused = false;
}

void GamePlay::SpawnSurfaces()
{
    sf::Sprite surface;
    surface.setTexture(m_context->m_assets->GetTexture(SURFACE));
    surface.setScale(5.f,1.f);
    int x = generateRandom();
    surface.setPosition(x, m_context->m_window->getSize().y);
    n_surfaces.push_back(surface);
}

int GamePlay::generateRandom()
{
    srand((unsigned) time(0));
    int randomNumber;
    for (int index = 0; index < 10; index++) {
        randomNumber = (rand() % (m_context->m_window->getSize().x-200)) + 32;
    }
    return randomNumber;
}

bool GamePlay::DeleteSurfaces()
{
    for(int i=0; i<n_surfaces.size();i++)
    {
        if(n_surfaces[i].getPosition().y <= 40)
        {
            n_surfaces.erase((n_surfaces.begin()));
            return true;
        }
    }
    return false;
}