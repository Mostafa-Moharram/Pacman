#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include "State.h"
#include "Definitions.h"
#include "Resources.h"
#include "PacMan.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Map.h"

class GameState : public State
{
private:
	PacMan pacman;
	PacMan lifes;
	int checktime[5] = { 15, 30, 45, 60, 85 };
	Blinky blinky;
	Pinky pinky;
	Inky inky;
	Clyde clyde;
	Ghost* ghosts[4];
	int mode = 0;
	float Time = 0.0f, cumtime = 0;;
	sf::Sound ballSound;
	sf::Sound powerUpSound;
	sf::Sound pacmanKill;
	sf::RectangleShape black;
	sf::Text text[4];
	bool Pause = false;
	int score = 0, Lifes = 3;
	void InitGame();

public:
	GameState();
	void HandleEvents(sf::Event& e) override;
	StateEvent Update(float dt) override;
	void Render() override;
	~GameState() override;
};

