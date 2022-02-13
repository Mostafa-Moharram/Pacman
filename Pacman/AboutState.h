#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "Resources.h"
#include "State.h"

class AboutState : public State
{
private:
	sf::Text text;
	sf::Text back;
	bool pressed;
public:
	AboutState();
	void Render() override;
	StateEvent Update(float dt) override;
	void HandleEvents(sf::Event& e) override;
};