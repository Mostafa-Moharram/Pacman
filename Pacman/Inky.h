#pragma once

#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Inky : public Ghost
{
private:
	sf::Vector2i* BlinkyTile;
protected:
	sf::Vector2i GetTarget() override;
	sf::Vector2i GetOut() override;
public:
	Inky();
	void SetBlinkyTile(sf::Vector2i* tile);
};

