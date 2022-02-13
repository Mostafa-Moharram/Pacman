#pragma once
#include<SFML/Graphics.hpp>

enum class StateEvents
{
	MenuEvents, AboutEvents, GameEvents, PauseEvents, Nothing
};

enum class MenuEvents
{
	Play, About, Exit
};

enum class GameEvents
{
	Pause, Win, Lose, Restart, ReturnToMenu
};

enum class PauseEvents
{
	Resume, ReturnToMenu
};

struct StateEvent
{
	 StateEvents type;
	 union
	 {
		 MenuEvents menuEvent;
		 GameEvents gameEvent;
		 PauseEvents pauseEvent;
	 };
};

class State
{
public:
	virtual void Render() = 0;
	virtual StateEvent Update(float dt) = 0;
	virtual void HandleEvents(sf::Event& e) = 0;
	virtual ~State();
	static sf::RenderWindow* window;
};


