#pragma once

#include "HealthBar.h"

class Player;

class PlayerController
{
public:
	PlayerController(Player* player);
	~PlayerController();

	float getHealth() const;
	float getMaxHealth() const;

	void modifyHealth(float change);
	void modifyMana(float change);

	void update();
	void draw(sf::RenderWindow& window);

	//members

public:

private:

	float m_health;
	float m_maxHealth;
	float m_mana;
	float m_maxMana;

	Player* m_player;
	HealthBar m_healthBar;

};

