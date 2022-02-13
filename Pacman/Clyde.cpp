#include "Clyde.h"

#include <cmath>

Clyde::Clyde() : Ghost(sf::Color(255, 165, 0))
{
	sprite.setColor(color);
}

sf::Vector2i Clyde::GetTarget()
{
	sf::Vector2i vec(0, 29);
	if (mode == GhostsMode::Chase)
	{
		sf::Vector2i temp = tile - PacmanTile;
		int dist = std::sqrt(temp.x * temp.x + temp.y + temp.y);
		if (dist > 7)
			vec = PacmanTile;
	}
	return vec;
}

sf::Vector2i Clyde::GetOut()
{
	return sf::Vector2i(13, 11);
}
