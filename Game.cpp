#include "Game.h"



Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SideScroller!");
	window.setFramerateLimit(60);

	playerTex.loadFromFile("Assets/barbarian boi.png");
	grassTex.loadFromFile("Assets/grass.png");

	platforms.push_back(sf::Sprite(grassTex));
	platforms.push_back(sf::Sprite(grassTex));
	platforms.push_back(sf::Sprite(grassTex));

	for (int i = 0; i < platforms.size(); i++) {
		
		platforms[i].setPosition(300 * i, 600);
	}

	Player player(playerTex, elapsed);
	player.setPosition(200, Helpers::GROUND_HEIGHT);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}

		elapsed = clock.restart().asSeconds();


		player.update();
		
		window.clear(sf::Color::Cyan);
		for (auto p : platforms)
		{
			window.draw(p);
		}
		window.draw(player);
		window.display();

	}
}

