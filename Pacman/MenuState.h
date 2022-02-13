#pragma once

#include "Definitions.h"
#include "Resources.h"
#include "State.h"

class MenuState : public State
{
private:
	sf::Text title;
	sf::Text text[3];
	sf::Sprite logo;
	bool pressed;
	float currentImageX;

public:
	MenuState();
	void Render() override;
	StateEvent Update(float dt) override;
	void HandleEvents(sf::Event& e) override;
};