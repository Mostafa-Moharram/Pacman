#include "Inky.h"

Inky::Inky() : Ghost(sf::Color::Cyan), BlinkyTile(nullptr)
{
	sprite.setColor(color);
}

void Inky::SetBlinkyTile(sf::Vector2i* tile)
{
	BlinkyTile = tile;
}

sf::Vector2i Inky::GetTarget()
{
	sf::Vector2i vec(26, 29);
	if (mode == GhostsMode::Chase)
	{
		const int* t = Tiles[static_cast<int>(PacmanDirection)];
		sf::Vector2i m = PacmanTile + 2 * sf::Vector2i(t[0], t[1]);
		vec = 2 * m - *BlinkyTile;
	}
	return vec;
}

sf::Vector2i Inky::GetOut()
{
	return sf::Vector2i(14, 11);
}
