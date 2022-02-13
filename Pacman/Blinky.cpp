#include "Blinky.h"

Blinky::Blinky() : Ghost(sf::Color::Red)
{
	sprite.setColor(color);
}

sf::Vector2i* Blinky::GetTile()
{
	return &tile;
}

sf::Vector2i Blinky::GetTarget()
{
	sf::Vector2i vec(26, 0);
	if (mode == GhostsMode::Chase)
		vec = PacmanTile;
	return vec;
}

sf::Vector2i Blinky::GetOut()
{
	return sf::Vector2i(14, 11);
}
