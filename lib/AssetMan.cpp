#include "AssetMan.hpp"

Engine::AssetMan::AssetMan()
{
}

Engine::AssetMan::~AssetMan()
{
}

void Engine::AssetMan::AddTexture(int id, string& filePath, bool wantRepeated = false)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(filePath))
    {
        if (wantRepeated)
        {
            texture->setRepeated(true);
        }

        m_textures[id] = std::move(texture);
    }
}
void Engine::AssetMan::AddFont(int id, string& filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
        m_fonts[id] = std::move(font);
    }
}

const Texture& Engine::AssetMan::GetTexture(int id) const
{
    return *(m_textures.at(id)).get();
}

const Font& Engine::AssetMan::GetFont(int id) const
{
    return *(m_fonts.at(id)).get();
}