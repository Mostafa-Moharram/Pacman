#pragma once
#include <SFML/Graphics.hpp>

extern const float AnimationRate;

extern const float CharacterScale;
extern const float MapObjectScale;

extern const float Padding;

extern const unsigned int XDimension;
extern const unsigned int YDimension;

extern const float MaxSpeed;

extern const float DirectionOffset[5][2];

extern const int Tiles[4][2];

enum class MapObjects
{
    Nothing, Dot, Wall, Gate, PowerBullet
}; // levels of MAPOBJECTS

enum class GhostsMode
{
    Scatter, Chase, Frightened, Eaten
};

enum class Direction
{
    Up, Left, Down, Right, Stop
};

struct MapObject
{
    MapObjects object = MapObjects::Nothing;
    sf::Sprite sprite;
};