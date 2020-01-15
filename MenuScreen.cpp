#include "MenuScreen.h"

#include <SFML/Graphics.hpp>

MenuScreen::MenuScreen()
{
}


MenuScreen::~MenuScreen()
{
}

int MenuScreen::run(sf::RenderWindow & window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return -1;
				break;
			}

		update();
		render(window);
	}

	//Load game screen
	return 1;
}

bool MenuScreen::loadContent()
{
	return false;
}

void MenuScreen::update()
{
}

void MenuScreen::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Cyan);
}
