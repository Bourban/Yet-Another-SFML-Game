#include "Game.h"
#include "Helpers.h"

extern bool Helpers::bDebugMode = false;

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

	platforms.push_back(Platform(grassTex, 0, 600));
	platforms.push_back(Platform(grassTex, 300, 600));
	platforms.push_back(Platform(grassTex, 600, 600));
	platforms.push_back(Platform(grassTex, 900, 600));

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
			if (Helpers::bDebugMode == true) 
			{
				window.draw(p.pls);
			}
		}
		window.draw(player);
		if (Helpers::bDebugMode == true)
		{
			window.draw(player.m_rect);
		}
		window.display();

	}
}

void Game::update()
{


}

