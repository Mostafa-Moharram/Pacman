#include "Resources.h"

sf::Font* Resources::font = nullptr;

sf::Texture* Resources::mapTexture = nullptr;
sf::Texture* Resources::pacmanTexture = nullptr;
sf::Texture* Resources::ghostTexture = nullptr;

sf::SoundBuffer* Resources::pacmanPowerUpBuffer = nullptr;
sf::SoundBuffer* Resources::pacmanKillBuffer = nullptr;
sf::SoundBuffer* Resources::pacmanDeadBuffer = nullptr;
sf::SoundBuffer* Resources::pacmanBallBuffer = nullptr;

 bool Resources::LoadResources()
 {
     font = new sf::Font;
     if (!font->loadFromFile("Resources/arial.ttf"))
         return false;

     mapTexture = new sf::Texture;
     if (!mapTexture->loadFromFile("Resources/tileset_pacman_map.png"))
         return false;

     pacmanTexture = new sf::Texture;
     if (!pacmanTexture->loadFromFile("Resources/tileset_pacman_player.png"))
         return false;


     ghostTexture = new sf::Texture;
     if (!ghostTexture->loadFromFile("Resources/tileset_pacman_ghost.png"))
         return false;

     pacmanPowerUpBuffer = new sf::SoundBuffer;
     if (!pacmanPowerUpBuffer->loadFromFile("Resources/pacman_powerup.wav"))
         return false;

     pacmanKillBuffer = new sf::SoundBuffer;
     if (!pacmanKillBuffer->loadFromFile("Resources/pacman_kill.wav"))
         return false;


     pacmanDeadBuffer = new sf::SoundBuffer;
     if (!pacmanDeadBuffer->loadFromFile("Resources/pacman_dead.wav"))
         return false;


     pacmanBallBuffer = new sf::SoundBuffer;
     if (!pacmanBallBuffer->loadFromFile("Resources/pacman_ball.wav"))
         return false;

     return true;

 }
 void Resources::FreeResources()
 {
     delete font;
     delete mapTexture;
     delete pacmanTexture;
     delete ghostTexture;
     delete pacmanPowerUpBuffer;
     delete pacmanKillBuffer;
     delete pacmanDeadBuffer;
     delete pacmanBallBuffer;
 }
