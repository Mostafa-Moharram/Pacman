#include "MenuState.h"

MenuState::MenuState() : currentImageX(0), pressed(false)
{
	logo.setPosition(400, 200);
	logo.setTexture(*Resources::pacmanTexture);
	logo.setTextureRect(sf::IntRect(0, 0, 15, 15));
	logo.setScale(4.f, 4.f);
	title.setFont(*Resources::font);
	title.setCharacterSize(40);
	title.setPosition(350, 275);
	title.setString("Pacman");
	for (int i = 0; i < 3; ++i)
	{
		text[i].setFont(*Resources::font);
		text[i].setCharacterSize(30);
		text[i].setPosition(400, 350 + i * 50);
		text[i].setFillColor(sf::Color::Blue);
	}
	text[0].setString("Play");
	text[1].setString("About");
	text[2].setString("Exit");
}

void MenuState::Render()
{
	window->draw(logo);
	window->draw(title);
	for (int i = 0; i < 3; ++i)
		window->draw(text[i]);
}

void MenuState::HandleEvents(sf::Event& e)
{
	pressed = false;
	if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
		pressed = true;
}

StateEvent MenuState::Update(float dt)
{
	StateEvent stateEvent{ StateEvents::Nothing };
	currentImageX += AnimationRate * dt;
	int temp = static_cast<int>(currentImageX);
	if (temp > 3)
	{
		currentImageX -= 4;
		temp -= 4;
	}
	logo.setTextureRect(sf::IntRect(temp * 15, 0, 15, 15));
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	for (int i = 0; i < 3; ++i)
	{
		if (text[i].getGlobalBounds().contains(mouse.x, mouse.y))
		{
			text[i].setFillColor(sf::Color::Yellow);
			if (pressed)
			{
				pressed = false;
				stateEvent.type = StateEvents::MenuEvents;
				stateEvent.menuEvent = static_cast<MenuEvents>(i);
			}
		}
		else
			text[i].setFillColor(sf::Color::Blue);
	}
	return stateEvent;
}