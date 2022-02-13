#include "GameState.h"

void GameState::InitGame()
{
	if (!Map::LoadMap())
		exit(0);
	black.setFillColor(sf::Color::Black);
	black.setPosition(28 * MapObjectScale * 15, 14 * MapObjectScale * 15);
	black.setSize(sf::Vector2f(MapObjectScale * 15, MapObjectScale * 15));
	pacman.SetPosition(Map::PacmanInitialPosition);
	blinky.SetPosition(Map::BlinkyInitialPosition);
	pinky.SetPosition(Map::PinkyInitialPosition);
	inky.SetPosition(Map::InkyInitialPosition);
	clyde.SetPosition(Map::ClydeInitialPosition);
	inky.SetBlinkyTile(blinky.GetTile());
	ballSound.setBuffer(*Resources::pacmanBallBuffer);
	powerUpSound.setBuffer(*Resources::pacmanPowerUpBuffer);
	pacmanKill.setBuffer(*Resources::pacmanKillBuffer);
	for (int i = 0; i < 4; i++)
	{
		text[i].setFont(*Resources::font);
		text[i].setCharacterSize(30);
	}
	text[0].setString("Time:");
	text[2].setString("Score:");
}

GameState::GameState()
{
	srand(static_cast<int>(time(nullptr)));
	InitGame();
	ghosts[0] = &blinky;
	ghosts[1] = &pinky;
	ghosts[2] = &inky;
	ghosts[3] = &clyde;
	text[0].setPosition(MapObjectScale * 15 * 28 + 50, 20);
	text[1].setPosition (MapObjectScale * 15 * 28 + 50, 70);
	text[2].setPosition(MapObjectScale * 15 * 28 + 50, 120 );
	text[3].setPosition(MapObjectScale * 15 * 28 + 50, 150 );
}

void GameState::HandleEvents(sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		switch (e.key.code)
		{
		case sf::Keyboard::Up:
			pacman.SetDirection(Direction::Up);
			break;
		case sf::Keyboard::Left:
			pacman.SetDirection(Direction::Left);
			break;
		case sf::Keyboard::Down:
			pacman.SetDirection(Direction::Down);
			break;
		case sf::Keyboard::Right:
			pacman.SetDirection(Direction::Right);
			break;
		case sf::Keyboard::Escape:
			Pause = true;
			break;
		}
		break;
	}
}

StateEvent GameState::Update(float dt)
{
	StateEvent stateEvent{ StateEvents::Nothing };
	if (Pause) {
		stateEvent.type = StateEvents::GameEvents;
		stateEvent.gameEvent = GameEvents::Pause;
		Pause = false;
		return stateEvent;
	}
	
	if (Map::DotsNumber == 0)
	{
		stateEvent.type = StateEvents::GameEvents;
		stateEvent.gameEvent = GameEvents::Win;
		return stateEvent;
	}
	text[1].setString(std::to_string(static_cast<int>(Time)));
	text[3].setString(std::to_string(score));
	Time += dt;
	switch (pacman.Move(dt))
	{
	case MapObjects::Dot:
		ballSound.play();
		score += 10;
		break;
	case MapObjects::PowerBullet:
		powerUpSound.play();
		score += 50;
		cumtime = 0;
		mode = 2;
		for (int i = 0; i < 4; ++i)
		if (ghosts[i]->GetMode() != GhostsMode::Eaten)
			ghosts[i]->SetMode(static_cast<GhostsMode>(mode));
		break;
	}
	for (int i = 0; i < 5; i++)
	{
		if (static_cast<int>(Time) == checktime[i])
		{
			mode = (1 + i) % 2;
			for (int i = 0; i < 4; ++i)
			{
				if (ghosts[i]->GetMode() != GhostsMode::Eaten && ghosts[i]->GetMode() != GhostsMode::Frightened)
				{
					ghosts[i]->SetMode(static_cast<GhostsMode>(mode));
				}
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		if (cumtime > 10 && ghosts[i]->GetMode() == GhostsMode::Frightened)
		{
			if (ghosts[i]->GetMode() != GhostsMode::Eaten && ghosts[i]->GetMode() == GhostsMode::Frightened)
			{
				mode = 1;
				ghosts[i]->SetMode(static_cast<GhostsMode>(mode));
			}
		}
		else if (ghosts[i]->GetMode() == GhostsMode::Frightened) {
			cumtime += dt;
			break;
		}
		
	}
	Ghost::PacmanTile = pacman.GetTile();
	Ghost::PacmanDirection = pacman.GetDirection();
	pacman.Animate(dt);
	for (int i = 0; i < 4; ++i)
	{
		ghosts[i]->Move(dt);
		ghosts[i]->Animate(dt);
		if (pacman.Hit(*ghosts[i]))
		{
			switch (ghosts[i]->GetMode())
			{
			case GhostsMode::Frightened:
				ghosts[i]->SetMode(GhostsMode::Eaten);
				pacmanKill.play();
				score += 100;
				break;
			case GhostsMode::Scatter:
			case GhostsMode::Chase:
				if (Lifes == 1)
				{
					stateEvent.type = StateEvents::GameEvents;
					stateEvent.gameEvent = GameEvents::Lose;
					sf::Sound dead(*Resources::pacmanDeadBuffer);
					dead.play();
					while (dead.getStatus() == sf::Sound::Playing);
					sf::SoundBuffer st;
					dead.setBuffer(st);
					return stateEvent;
				}
				pacman.SetPosition(Map::PacmanInitialPosition);
				blinky.SetPosition(Map::BlinkyInitialPosition);
				pinky.SetPosition(Map::PinkyInitialPosition);
				inky.SetPosition(Map::InkyInitialPosition);
				clyde.SetPosition(Map::ClydeInitialPosition);
				Lifes--;
				for (int i = 0; i < 4; ++i)
				ghosts[i]->SetMode(GhostsMode::Chase);
				break;
			}
		}
	}

	return stateEvent;
}

void GameState::Render()
{
	for (int i = 0; i < Lifes; i++) {
		lifes.Draw(*window);
		lifes.SetPosition(sf::Vector2f(MapObjectScale * 15 * 28 + 50, 220 + 25 * i));
	}
	for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j < 28; ++j)
			window->draw(Map::Objects[i][j].sprite);
	}

	for (int i = 0; i < 4; ++i)
		ghosts[i]->Draw(*window);

	pacman.Draw(*window);
	for (int i = 0; i < 4; i++)
		window->draw(text[i]);
	window->draw(black);
}

GameState::~GameState()
{
	Map::DotsNumber = 0;
	sf::SoundBuffer sb;
	ballSound.setBuffer(sb);
	powerUpSound.setBuffer(sb);
	pacmanKill.setBuffer(sb);
}




