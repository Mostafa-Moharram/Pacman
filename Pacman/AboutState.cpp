#include "AboutState.h"

AboutState::AboutState() : pressed(false)
{
	text.setFont(*Resources::font);
	text.setCharacterSize(30);
	text.setPosition(100, 200);
	const char* const txt = 
R"(The programmers contributed to this game:
	Mostafa Moharram
	Mohammed Ashraf
	Mostafa Ayman
	Menna Yehia
	Mariam Yasser
)";
	text.setString(txt);
	back.setFont(*Resources::font);
	back.setCharacterSize(30);
	back.setPosition(400, 600);
	back.setString("Back");
	back.setFillColor(sf::Color::Blue);
}

void AboutState::Render()
{
	window->draw(text);
	window->draw(back);
}

StateEvent AboutState::Update(float dt)
{
	StateEvent stateEvent{ StateEvents::Nothing };
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	if (back.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		back.setFillColor(sf::Color::Yellow);
		if (pressed)
		{
			pressed = false;
			stateEvent.type = StateEvents::AboutEvents;
		}
	}
	else
		back.setFillColor(sf::Color::Blue);
	return stateEvent;
}

void AboutState::HandleEvents(sf::Event& e)
{
	pressed = false;
	if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
		pressed = true;
}
