#pragma once

#include <SFML\Graphics.hpp>

#include "Player.h"
#include "Screen.h"
#include "Helpers.h"
#include "Platform.h"
#include "Pickup.h"

class Game : public Screen
{
public:
	Game();

	~Game();

	bool loadContent();

	void update();
	void render(sf::RenderWindow &window);

	int run(sf::RenderWindow &window);

	void cleanup();

	//Variables

private:
	sf::Clock clock;
	double elapsed;

	float timeSinceLastUpdate;

	std::vector<Platform*> platforms;
	std::vector<Pickup*> pickups;

	sf::Texture playerTex;
	sf::Texture grassTex;
	sf::Texture cheeseTex;

	Player* p_player;

};

