#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Definitions.h"
#include "Resources.h"
#include "MenuState.h"
#include "AboutState.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameResult.h"

class Game
{
private:
	sf::RenderWindow window;
	std::stack<State*> states;
	bool Switch(StateEvent stateEvents);
public:
	Game();
	void Run();
	~Game();
};