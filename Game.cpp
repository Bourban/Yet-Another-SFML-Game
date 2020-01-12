#include "Game.h"
#include "Helpers.h"

extern bool Helpers::bDebugMode = false;

Game::Game() : window(sf::VideoMode(1280, 720), "SideScroller!")
{
}

Game::~Game()
{
	delete p_player;
}

void Game::run()
{
	window.setFramerateLimit(60);

	//These need to be loaded in the scope of run()
	playerTex.loadFromFile("Assets/barbarian boi.png");
	grassTex.loadFromFile("Assets/grass.png");

	platforms.push_back(Platform(grassTex, 0, 600));
	platforms.push_back(Platform(grassTex, 300, 600));
	platforms.push_back(Platform(grassTex, 600, 600));
	platforms.push_back(Platform(grassTex, 900, 600));

	p_player = new Player(playerTex, elapsed);

	p_player->setPosition(200, Helpers::GROUND_HEIGHT);

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

		p_player->update();
		
		render();

	}
}

void Game::render() 
{
	window.clear(sf::Color::Cyan);
	for (auto p : platforms)
	{
		window.draw(p);
		if (Helpers::bDebugMode == true)
		{
			window.draw(p.pls);
		}
	}
	window.draw(*p_player);
	if (Helpers::bDebugMode == true)
	{
		window.draw((p_player->m_rect));
	}
	window.display();
}

void Game::update()
{

}

