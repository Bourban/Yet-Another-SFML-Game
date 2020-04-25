#include <SFML/Graphics/RenderWindow.hpp>

#include "Screens.h"

/* Player animations from https://thomasgvd.itch.io/barbarian */

int main() {

	std::vector<Screen*> screens;

	sf::RenderWindow window(sf::VideoMode(Helpers::SCREEN_WIDTH, Helpers::SCREEN_HEIGHT), "Platformy thing");
	window.setFramerateLimit(60.0f);

	/*SCREEN INDEX:
	0 -- Main Menu
	1 -- Game Screen

	*/

	int currentScreen = 0;

	MenuScreen menu;
	screens.push_back(&menu);

	GameScreen game;
	screens.push_back(&game);

	while (currentScreen >= 0 && currentScreen <= screens.size()) 
	{
		currentScreen = screens[currentScreen]->run(window);
	}

	return currentScreen;

}