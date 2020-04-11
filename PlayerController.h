#pragma once

#include "HealthBar.h"
#include "CharacterController.h"

class Player;

class PlayerController : public CharacterController
{
public:
	PlayerController(Player* player);
	~PlayerController();

	void addTexturesToBars(sf::Texture& bgTex, sf::Texture& barTexHealth, sf::Texture& barTexMana);

	void modifyHealth(float change);
	void modifyMana(float change);

	void update(double &elapsed);
	void draw(sf::RenderWindow& window);

//members

public:

private:

	Player* m_player;
	HealthBar m_healthBar;
	HealthBar m_manaBar;

};

