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

}



void Game::update()
{
	std::vector<Platform*>::iterator itt = platforms.begin();
	while(platforms.size()  && itt != platforms.end())
	{
		Platform* p = *itt;

		if (p_player->m_feetBox.intersects(p->getTop()) && p_player->getDeltaY() < 0)
		{
			p_player->setIsTouchingFloor(true);
			break;
		}
		else
		{
			itt++;
		}


		p_player->setIsTouchingFloor(false);
	}

	std::vector<Pickup*>::iterator it = pickups.begin();
	while(pickups.size()  && it != pickups.end())
	{
		Pickup* p = *it;

		if (p_player->m_feetBox.intersects(p->getRect()))
		{
			p->onPickup(p_player);
			it = pickups.erase(it);
		}
		else
		{
			++it; 
		}
	}

	/*for (auto &p : pickups)
	{
		if (p_player->m_feetBox.intersects(p->getRect()))
		{
			p->onPickup(p_player);
			delete p;
		}
	}*/

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
	if (!grassTex.loadFromFile("Assets/grass.png")) 
	{
		return false;
	}
	if (!cheeseTex.loadFromFile("Assets/Item_65.png")) 
	{
		return false;
	}

	pickups.push_back(std::move(new Pickup(sf::Vector2f(300, 580), cheeseTex, health, 20.0f)));
	pickups.push_back(std::move(new Pickup(sf::Vector2f(340, 580), cheeseTex, health, 20.0f)));

	platforms.push_back(std::move(new Platform(grassTex, 0, 600)));
	platforms.push_back(std::move(new Platform(grassTex, 300, 600)));
	platforms.push_back(std::move(new Platform(grassTex, 900, 600)));

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