#pragma once
#include "Screen.h"
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

};

