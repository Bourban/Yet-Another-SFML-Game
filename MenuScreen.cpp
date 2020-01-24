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
	if (!loadContent()) {
		return -5;
	}

	

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return -1;
				
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Return) 
				{
					return 1;

				}

				break;
			}

		update();
		render(window);
	}
}

bool MenuScreen::loadContent()
{
	if (!font.loadFromFile("Assets/Fonts/Regular.otf")) {
		return false;
	}

	advanceText.setString("Press Enter to play!");
	advanceText.setFont(font);
	advanceText.setCharacterSize(32);
	advanceText.setColor(sf::Color::Black);
	//TODO: offset width and height of text
	advanceText.setOrigin(advanceText.getLocalBounds().width / 2, advanceText.getLocalBounds().height / 2);
	advanceText.setPosition(Helpers::SCREEN_WIDTH / 2, Helpers::SCREEN_HEIGHT / 2);

	return true;
}

void MenuScreen::update()
{
}

void MenuScreen::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Cyan);
	window.draw(advanceText);
	window.display();
}
