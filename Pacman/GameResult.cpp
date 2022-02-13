#include "GameResult.h"

GameResult::GameResult(State* state, std::string result) : pressed(false)
{
	this->state = state;

	box.setSize(sf::Vector2f(450, 400));
	box.setFillColor(sf::Color::Black);
	box.setPosition(sf::Vector2f(390, 190));

	text[0].setPosition(400, 200);
	text[1].setPosition(450, 350);
	text[2].setPosition(450, 400);
	for (int i = 0; i < 3; i++)
		text[i].setFont(*Resources::font);
	text[0].setString(result);
	text[0].setCharacterSize(70);
	text[1].setString("Restart");
	text[1].setCharacterSize(30);
	text[2].setString("Return To Menu");
	text[2].setCharacterSize(30);
}

void GameResult::Render()
{
	this->state->Render();
	window->draw(box);
	for (int i = 0; i < 3; ++i)
		window->draw(text[i]);
}

void GameResult::HandleEvents(sf::Event& e)
{
	pressed = false;
	if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
		pressed = true;
}


StateEvent GameResult::Update(float dt)
{
	StateEvent stateEvent{ StateEvents::Nothing };
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	for (int i = 1; i < 3; ++i)
	{
		if (text[i].getGlobalBounds().contains(mouse.x, mouse.y))
		{
			text[i].setFillColor(sf::Color::Yellow);
			if (pressed)
			{
				stateEvent.type = StateEvents::GameEvents;
				stateEvent.gameEvent = static_cast<GameEvents>(i+2);
			}
		}
		else
			text[i].setFillColor(sf::Color::Blue);
	}
	return stateEvent;
}
