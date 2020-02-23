#include "PlayerController.h"

#include "Player.h"
#include <iostream>

PlayerController::PlayerController(Player* player) : m_player(player), m_healthBar(sf::Vector2f(20, 20), 200, this), m_health(50.0f), m_maxHealth(100.0f),
														m_mana(50.0f), m_maxMana(100.0f)
{

}


PlayerController::~PlayerController()
{
}

float PlayerController::getHealth() const
{
	return m_health;
}

float PlayerController::getMaxHealth() const
{
	return m_maxHealth;
}

void PlayerController::modifyHealth(float change)
{
	m_health += change;
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
	else if (m_health <= 0.0f)
	{
		m_player->setState(dying);
	}
}

void PlayerController::modifyMana(float change)
{
	m_mana += change;
	if (m_mana > m_maxMana)
	{
		m_mana = m_maxMana;
	}
	else if (m_mana <= 0.0f)
	{
		m_mana = 0.0f;
	}
}

void PlayerController::update()
{
	std::cout << m_health << std::endl;
	m_healthBar.update();
}

void PlayerController::draw(sf::RenderWindow& window)
{
	m_healthBar.draw(window);
}
