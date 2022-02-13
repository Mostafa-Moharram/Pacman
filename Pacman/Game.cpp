#include "Game.h"

Game::Game()
	: window(sf::VideoMode(XDimension, YDimension), "", sf::Style::None)
{
	window.setFramerateLimit(60);
	State::window = &window;
	if (!Resources::LoadResources())
		exit(0);
}

void Game::Run()
{
	states.push(new MenuState);
	sf::Clock ck;
	while (!states.empty())
	{
		sf::Event e;
		while (window.pollEvent(e))
			states.top()->HandleEvents(e);
		StateEvent stateEvent = states.top()->Update(ck.restart().asSeconds());
		if (Switch(stateEvent))
			continue;
		window.clear();
		states.top()->Render();
		window.display();
	}
}

Game::~Game()
{
	window.close();
	Resources::FreeResources();
}

bool Game::Switch(StateEvent stateEvent)
{
	switch (stateEvent.type)
	{
	case StateEvents::MenuEvents:
		switch (stateEvent.menuEvent)
		{
		case MenuEvents::Play:
			states.push(new GameState);
			return true;
		case MenuEvents::About:
			states.push(new AboutState);
			return true;
		case MenuEvents::Exit:
			delete states.top();
			states.pop();
			window.close();
			return true;
		}
	case StateEvents::GameEvents:
		switch (stateEvent.gameEvent)
		{
		case GameEvents::Pause:
			states.push(new PauseState(states.top()));
			return true;
		case GameEvents::Lose:
			states.push(new GameResult(states.top(), "You Lost!"));
			return true;
		case GameEvents::Win:
			states.push(new GameResult(states.top(), "You Won!"));
			return true;
		case GameEvents::Restart:
			delete states.top();
			states.pop();
			delete states.top();
			states.pop();
			states.push(new GameState());
			return true;
		case GameEvents::ReturnToMenu:
			delete states.top();
			states.pop();
			delete states.top();
			states.pop();
			return true;
		}
	case StateEvents::PauseEvents:
		switch (stateEvent.pauseEvent)
		{
		case PauseEvents::Resume:
			delete states.top();
			states.pop();
			return true;
		case PauseEvents::ReturnToMenu:
			delete states.top();
			states.pop();
			delete states.top();
			states.pop();
			return true;
		}
	case StateEvents::AboutEvents:
		delete states.top();
		states.pop();
		return true;
	}
	return false;
}