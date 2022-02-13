#include "Definitions.h"

// 20.0f
const float AnimationRate = 20.0f;
// 1.4f M: 1.0f
const float CharacterScale = 1.4f;
// 2.0f M: 1.6f
const float MapObjectScale = 2.0f;

const float Padding = (MapObjectScale - CharacterScale) * 15 / 2.0f;
// 840
const unsigned int XDimension = 28 * 15 * MapObjectScale + 270;

const unsigned int YDimension = 31 * 15 * MapObjectScale;
// 110.0f M: 80.0f
const float MaxSpeed = 110.0f;

const float DirectionOffset[5][2]
{
    {  0.0f,     -MaxSpeed },   // Move up
    { -MaxSpeed,  0.0f     },   // Move left
    {  0.0f,      MaxSpeed },   // Move down
    {  MaxSpeed,  0.0f     },   // Move right
    {  0.0f,      0.0f     }    // Stop    
};

const int Tiles[4][2]
{
    {  0, -1 },
    { -1,  0 },
    {  0,  1 },
    {  1,  0 }
};