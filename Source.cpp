#include <SFML/Graphics/RenderWindow.hpp>

#include "Screens.h"
#include "Game.h"

/* Player animations from https://thomasgvd.itch.io/barbarian */

int main() {

	std::vector<Screen*> screens;

	sf::RenderWindow window(sf::VideoMode(Helpers::SCREEN_WIDTH, Helpers::SCREEN_HEIGHT), "Platformy thing");
	window.setFramerateLimit(60.0f);

	int currentScreen = 0;

	Game game;
	screens.push_back(&game);


	while (currentScreen >= 0) 
	{
		currentScreen = screens[currentScreen]->run(window);
	}

	return 0;
	
}