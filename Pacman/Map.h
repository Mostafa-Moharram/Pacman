#pragma once

#include <SFML/Graphics.hpp>
#include <cstring>
#include <fstream>
#include "Definitions.h"
#include "Resources.h"

namespace Map
{
	extern sf::Vector2f PacmanInitialPosition;
	extern sf::Vector2f BlinkyInitialPosition;
	extern sf::Vector2f PinkyInitialPosition;
	extern sf::Vector2f InkyInitialPosition;
	extern sf::Vector2f ClydeInitialPosition;

	extern int DotsNumber;

	extern MapObject Objects[31][28];

	bool LoadMap();
}