#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Helpers.h"
#include "Platform.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	void update();

private:
	sf::Clock clock;
	double elapsed;

	std::vector<sf::Sprite> platforms;

	sf::Texture playerTex;
	sf::Texture grassTex;

};

