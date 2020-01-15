#pragma once

#include <SFML\Graphics.hpp>

#include "Player.h"
#include "Screen.h"
#include "Helpers.h"
#include "Platform.h"

class Game : public Screen
{
public:
	Game();
	~Game();

	bool loadContent();

	void update();
	void render(sf::RenderWindow &window);

	int run(sf::RenderWindow &window);

	//Variables

private:
	sf::Clock clock;
	double elapsed;

	float timeSinceLastUpdate;

	std::vector<Platform> platforms;

	sf::Texture playerTex;
	sf::Texture grassTex;

	Player* p_player;

};

