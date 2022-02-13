#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Resources.h"
#include "Definitions.h"
#include "Map.h"
#include "Ghost.h"

class PacMan
{
private:
    float currentImageX;
    sf::RectangleShape sprite;
    Direction direction;
    Direction setDirection;
    Direction face;
    MapObjects Collides(MapObject& o) const;
    bool CheckBoundary(sf::Vector2f vec) const;
    MapObjects Valid(Direction dir, sf::Vector2f& vec);
public:
    PacMan();
    MapObjects Move(float dt);
    sf::Vector2i GetTile() const;
    Direction GetDirection() const;
    bool Hit(Ghost& ghost) const;
    void SetPosition(sf::Vector2f InitialPosition);
    void SetDirection(Direction dir);
    void Animate(float dt);
    void Draw(sf::RenderWindow& window);
};