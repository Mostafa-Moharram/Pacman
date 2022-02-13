#include "Pinky.h"

Pinky::Pinky() : Ghost(sf::Color(255, 192, 203))
{
	sprite.setColor(color);
}

sf::Vector2i Pinky::GetTarget()
{
	sf::Vector2i vec(0, 0);
	if (mode == GhostsMode::Chase)
	{
		const int* t = Tiles[static_cast<int>(PacmanDirection)];
		vec = PacmanTile + 4 * sf::Vector2i(t[0], t[1]);
	}
	return vec;
}

sf::Vector2i Pinky::GetOut()
{
	return sf::Vector2i(13, 11);
}
