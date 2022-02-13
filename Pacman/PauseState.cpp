#include "PauseState.h"

PauseState::PauseState(State* state) : pressed(false)
{
	this->state = state;
	box.setSize(sf::Vector2f(300, 400));
	box.setFillColor(sf::Color::Black);
	box.setPosition(sf::Vector2f(390, 190));

	text[2].setPosition(400, 200);
	text[0].setPosition(450, 350);
	text[1].setPosition(450, 400);
	for (int i = 0; i < 3; i++)
		text[i].setFont(*Resources::font);
	text[2].setString("Pause");
	text[2].setCharacterSize(70);
	text[0].setString("Resume");
	text[0].setCharacterSize(30);
	text[1].setString("Return To Menu");
	text[1].setCharacterSize(30);
}

void PauseState::Render()
{
	this->state->Render();
	window->draw(box);
	for (int i = 0; i < 3; ++i)
		window->draw(text[i]);
}

void PauseState::HandleEvents(sf::Event& e)
{
	pressed = false;
	if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
		pressed = true;
}

StateEvent PauseState::Update(float dt)
{
	StateEvent stateEvent{ StateEvents::Nothing };
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	for (int i = 0; i < 2; ++i)
	{
		if (text[i].getGlobalBounds().contains(mouse.x, mouse.y))
		{
			text[i].setFillColor(sf::Color::Yellow);
			if (pressed)
			{
				stateEvent.type = StateEvents::PauseEvents;
				stateEvent.pauseEvent = static_cast<PauseEvents>(i);
			}
		}
		else
			text[i].setFillColor(sf::Color::Blue);
	}
	return stateEvent;
}