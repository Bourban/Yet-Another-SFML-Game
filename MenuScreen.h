#pragma once
#include "Screen.h"
#include "Helpers.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuScreen :
	public Screen
{
public:
	MenuScreen();
	~MenuScreen();

	int run(sf::RenderWindow &window);

	bool loadContent();

	void update();
	void render(sf::RenderWindow &window);

private:

	//Class Members

public:

private:

	sf::Font font;
	sf::Text advanceText;
};

