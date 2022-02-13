#pragma once

#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Pinky : public Ghost
{
protected:
	sf::Vector2i GetTarget() override;
	sf::Vector2i GetOut() override;
public:
	Pinky();
};

