#pragma once
#include "State.h"
#include "Definitions.h"
#include "Resources.h"
#include "PacMan.h"

class PauseState : public State
{
private:
	State* state;
	bool pressed;
	sf::Text text[3];
	sf::RectangleShape box;
	
public:
	PauseState(State* state);
	void Render() override;
	void HandleEvents(sf::Event& e) override;
	StateEvent Update(float dt) override;
};

