#pragma once

#include <SFML\Graphics.hpp>

#include "Player.h"
#include "Screen.h"
#include "Helpers.h"
#include "Platform.h"
#include "Pickup.h"
#include "Projectile.h"
#include "BGSprite.h"

class Game : public Screen
{
public:

	Game();
	~Game();

	bool loadContent();

	virtual void update();
	void render(sf::RenderWindow &window);

	int run(sf::RenderWindow &window);

	void cleanup();

	//Variables

protected:
	sf::Clock clock;
	double elapsed;

	float timeSinceLastUpdate;

	//Consider changing to smart pointers, current method should work fine but this is more modern C++ -- handles the deleting itself when out of scope 

	//std::vector<std::unique_ptr<Platform>> platforms;
	std::vector<std::unique_ptr<Pickup>> pickups;
	//std::vector<std::unique_ptr<Projectile>> projectiles;
	//std::vector<std::unique_ptr<sf::Sprite>> backgroundSprites;

	std::vector<Platform*> platforms;
	/*std::vector<Pickup*> pickups;*/
	std::vector<Projectile*> projectiles;
	std::vector<sf::Sprite*> backgroundSprites;

	sf::Texture playerTex;
	sf::Texture grassTex;
	sf::Texture cheeseTex;
	sf::Texture projectileTex;
	sf::Texture treeTex;
	sf::Texture bannerTex;

	std::unique_ptr<Player> p_player;
};

