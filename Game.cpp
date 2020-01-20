#include "Game.h"
#include "Helpers.h"

extern bool Helpers::bDebugMode = false;

Game::Game() : timeSinceLastUpdate(0.0f), p_player(nullptr)
{

}

Game::~Game()
{
	if(p_player != nullptr)
	delete p_player;
}

int Game::run(sf::RenderWindow &window) 
{

	if (!loadContent()) 
	{
		return -1;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return -1;
				break;
			}
		//reset the clock between frames
		elapsed = clock.restart().asSeconds();

		//Main loop functions here
		update();	
		render(window);
	}
}



void Game::update()
{
	for each (Platform p in platforms)
	{
		if (p_player->m_feetBox.intersects(p.getTop()) && p_player->getDeltaY() < 0)
		{
			p_player->setIsTouchingFloor(true);
			break;
		}

		p_player->setIsTouchingFloor(false);
	}

	p_player->update();

}

bool Game::loadContent() 
{
	if (!playerTex.loadFromFile("Assets/barbarian boi.png")) 
	{
		return false;
	}
	if (!grassTex.loadFromFile("Assets/grass.png")) 
	{
		return false;
	}

	platforms.push_back(Platform(grassTex, 0, 600));
	platforms.push_back(Platform(grassTex, 300, 600));
	platforms.push_back(Platform(grassTex, 900, 600));

	p_player = new Player(playerTex, elapsed);

	p_player->setPosition(200, 400);


	return true;
}

void Game::render(sf::RenderWindow &window)
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