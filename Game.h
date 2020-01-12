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
	void render();


	//Variables

private:
	sf::Clock clock;
	double elapsed;

	sf::RenderWindow window;

	std::vector<Platform> platforms;

	sf::Texture playerTex;
	sf::Texture grassTex;

	Player* p_player;

};

