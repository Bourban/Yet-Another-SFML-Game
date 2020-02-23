#include "Game.h"
#include "Helpers.h"

extern bool Helpers::bDebugMode = false;

Game::Game() : timeSinceLastUpdate(0.0f), p_player(nullptr)
{

}

Game::~Game()
{

}

int Game::run(sf::RenderWindow &window) 
{
	if (!loadContent()) 
	{
		return -5;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return -1;
				
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					return 0;
				}

			default:
				break;
			}
			
		//reset the clock between frames
		elapsed = clock.restart().asSeconds();

		//Main loop functions here
		update();	
		render(window);
	}

	cleanup();
}

void Game::cleanup()
{
	if (p_player)
	{
		delete p_player;
	}

	for (auto p : pickups) 
	{
		delete p;
	}
	pickups.clear();

	for (auto p : platforms) 
	{
		delete p;
	}
	platforms.clear();
}




void Game::update()
{
	std::vector<Platform*>::iterator iter_plat = platforms.begin();
	while(platforms.size()  && iter_plat != platforms.end())
	{
		Platform* p = *iter_plat;

		if (p_player->m_feetBox.intersects(p->getTop()) && p_player->getDeltaY() < 0)
		{
			p_player->setIsTouchingFloor(true);
			break;
		}
		else
		{
			iter_plat++;
		}

		p_player->setIsTouchingFloor(false);
	}

	std::vector<Pickup*>::iterator it = pickups.begin();
	while(pickups.size()  && it != pickups.end())
	{
		Pickup* p = *it;

		if (p_player->getBody().intersects(p->getRect()))
		{
			p->onPickup(p_player->getController());
			it = pickups.erase(it);
		}
		else
		{
			++it; 
		}
	}

	if (elapsed > Helpers::MS_PER_UPDATE) 
	{
		elapsed = Helpers::MS_PER_UPDATE;
	}

	p_player->update();

}

bool Game::loadContent() 
{
	if (!playerTex.loadFromFile("Assets/barbarian boi.png")) 
	{
		return false;
	}
	if (!grassTex.loadFromFile("Assets/NewGrass.png")) 
	{
		return false;
	}
	if (!cheeseTex.loadFromFile("Assets/Item_65.png")) 
	{
		return false;
	}

	pickups.push_back(std::move(new Pickup(sf::Vector2f(300, 570), cheeseTex, health, 20.0f)));
	pickups.push_back(std::move(new Pickup(sf::Vector2f(340, 570), cheeseTex, health, 20.0f)));
	pickups.push_back(std::move(new Pickup(sf::Vector2f(940, 570), cheeseTex, health, 20.0f)));

	platforms.push_back(std::move(new Platform(grassTex, 0, 600, sf::Vector2f(0.1, 0.1))));
	platforms.push_back(std::move(new Platform(grassTex, 260, 600, sf::Vector2f(0.15, 0.1))));
	platforms.push_back(std::move(new Platform(grassTex, 900, 600, sf::Vector2f(0.15, 0.1))));

	p_player = new Player(playerTex, elapsed);

	p_player->setPosition(200, 400);


	return true;
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Cyan);
	for (auto p : platforms)
	{
		window.draw(*p);
		if (Helpers::bDebugMode == true)
		{
			window.draw(p->pls);
		}
	}

	for (auto &p : pickups)
	{
		if (p) 
		{
			window.draw(*p);
		}
	}
	
	p_player->draw(window);
	
	if (Helpers::bDebugMode == true)
	{
		window.draw((p_player->m_rect));
	}
	window.display();
}