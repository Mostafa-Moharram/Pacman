#pragma once
#include <SFML/Graphics.hpp>

#include <algorithm>
#include <utility>
#include <cstdlib>
#include <vector>

#include "Definitions.h"
#include "Resources.h"
#include "Map.h"

class PacMan;

class Ghost
{
    friend PacMan;
private:
    float currentImageG;
    sf::Vector2i preTile;
    Direction direction;
    GhostsMode setMode;
    GhostsMode preMode;
    void Eaten();
    void Frightened();
    void Chase(sf::Vector2i target);
    void Center(Direction newDir);
    bool EdgeCheck();
    void SetTextureRect(int offset, int num, float dt);
    void Reverse();

protected:
    sf::Vector2i tile;
    sf::Color color;
    sf::Sprite sprite;
    GhostsMode mode;
    virtual sf::Vector2i GetTarget() = 0;
    virtual sf::Vector2i GetOut() = 0;

 public:  
    Ghost(sf::Color _color);
    void SetPosition(sf::Vector2f ghostInitialPosition);
    void Move(float dt);
    void Animate(float dt);
    void SetMode(GhostsMode _mode);
    void Draw(sf::RenderWindow& window);
    GhostsMode GetMode() const;

    static Direction PacmanDirection;
    static sf::Vector2i PacmanTile;
};