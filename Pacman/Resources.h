#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Resources
{
    extern sf::Font* font;
    
    extern sf::Texture* mapTexture;
    extern sf::Texture* pacmanTexture;
    extern sf::Texture* ghostTexture;
    
    extern sf::SoundBuffer* pacmanPowerUpBuffer;
    extern sf::SoundBuffer* pacmanKillBuffer;
    extern sf::SoundBuffer* pacmanDeadBuffer;
    extern sf::SoundBuffer* pacmanBallBuffer;

    bool LoadResources();
    void FreeResources();
}

