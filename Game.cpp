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

	//Restart the clock before the first update, otherwise the cumulative time on the menu causes issues on the very first frame
	clock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				cleanup();
				return -1;
				
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					cleanup();
					return 0;
				}
				if( event.key.code == sf::Keyboard::E) //temporary solution to test the projectiles functionality
				{
					//projectiles.push_back(std::move(new Projectile(elapsed, projectileTex, sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(1500, 550), EnemyTeam, 100.0f, 20.0f, sf::Vector2f(-0.1f, 0.1f))));
					projectiles.push_back(std::move(new Projectile(elapsed, projectileTex, sf::Vector2f(1.0f, 0.0f), sf::Vector2f(p_player->getPosition()), PlayerTeam, 150.0f, 20.0f, sf::Vector2f(0.1f, 0.1f))));
					break;
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
		//not necessary?
		p_player.reset();
	}

	for (auto &p : pickups) 
	{
		//Not necessary with smart pointers
		//delete p;
	}
	pickups.clear();

	for (auto &p : platforms) 
	{
		delete p;
	}

	for (auto &p : projectiles) 
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

	std::vector<Projectile*>::iterator iter_projectiles = projectiles.begin();

	while (projectiles.size() && iter_projectiles != projectiles.end())
	{
		Projectile* p = *iter_projectiles;

		p->update();

		//Check if off-screen too

		if (p->getOwner() == PlayerTeam)
		{
			//Check for collision against all enemies -- function takes care of OnHit
			
			// if hit, erase, if not increment

			iter_projectiles++;
		}
		else if (p->getOwner() == EnemyTeam)
		{
			if (p->checkCollision(*p_player)) //This will also call onHit if true!
			{
				iter_projectiles = projectiles.erase(iter_projectiles);
			}
			else {
				iter_projectiles++;
			}
		}
	}

	for(auto&& p : pickups)
	{
		if (p_player->getBody().intersects(p->getRect()))
		{
			p->onPickup(p_player->getController());
			pickups.erase(std::remove(pickups.begin(), pickups.end(), p), pickups.end());
			//break isn't an ideal solution, as we don't check the rest of the vector after this one, but this does run every frame, so any overlapping pickup can be processed on the next frame
			break;
		}
	}

	/*std::vector<Pickup*>::iterator it = pickups.begin();

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
	if (!grassTex.loadFromFile("Assets/NewGrass.png")) 
	{
		return false;
	}
	if (!cheeseTex.loadFromFile("Assets/Item_65.png")) 
	{
		return false;
	}
	if (!projectileTex.loadFromFile("Assets/fireballsmall.png"))
	{
		return false;
	}
	if(!treeTex.loadFromFile("Assets/tree_fin.png"))
	{
		return false;
	}
	if(!bannerTex.loadFromFile("Assets/Sorcerer_Banner.png"))
	{
		return false;
	}

	backgroundSprites.push_back(std::move(new sf::Sprite(treeTex)));
	backgroundSprites.push_back(std::move(new sf::Sprite(treeTex)));

	//this will go out of scope at the end of the function, still come up with a better solution though
	int i = 0;

	for (auto &s : backgroundSprites )
	{
		s->setOrigin(sf::Vector2f(s->getTexture()->getSize().x / 2, s->getTexture()->getSize().y /2));
		s->setScale(sf::Vector2f(0.15f, 0.15f));
		s->setPosition(sf::Vector2f(400 +(600 * i), 480));
		i++;
	}

	pickups.push_back(std::make_unique<Pickup>(sf::Vector2f(300, 570), cheeseTex));
	pickups.push_back(std::make_unique<Pickup>(sf::Vector2f(340, 570), cheeseTex));
	pickups.push_back(std::make_unique<Pickup>(sf::Vector2f(940, 570), cheeseTex));

	/*pickups.push_back(std::move(new Pickup(sf::Vector2f(300, 570), cheeseTex, health, 20.0f)));
	pickups.push_back(std::move(new Pickup(sf::Vector2f(340, 570), cheeseTex)));
	pickups.push_back(std::move(new Pickup(sf::Vector2f(940, 570), cheeseTex, health, 20.0f)));*/

	platforms.push_back(std::move(new Platform(grassTex, 0, 600, sf::Vector2f(0.1, 0.1))));
	platforms.push_back(std::move(new Platform(grassTex, 260, 600, sf::Vector2f(0.15, 0.1))));
	platforms.push_back(std::move(new Platform(grassTex, 900, 600, sf::Vector2f(0.15, 0.1))));

	projectiles.push_back(std::move(new Projectile(elapsed, projectileTex, sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(1500, 550), EnemyTeam, 100.0f, 20.0f ,sf::Vector2f(-0.1f, 0.1f))));
	projectiles.push_back(std::move(new Projectile(elapsed, projectileTex, sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(1550, 550), EnemyTeam, 100.0f, 20.0f, sf::Vector2f(-0.1f, 0.1f))));

	p_player = std::unique_ptr<Player>(new Player(playerTex, elapsed));

	p_player->setPosition(200, 400);

	return true;
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Cyan);

	for (auto &p : backgroundSprites)
	{
		window.draw(*p);
	}

	for (auto &p : platforms)
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
	
	for(auto &p : projectiles)
	{
		window.draw(*p);
	}

	p_player->draw(window);
	
	if (Helpers::bDebugMode == true)
	{
		window.draw((p_player->m_rect));
	}
	window.display();
}