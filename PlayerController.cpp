#include "PlayerController.h"

#include "Player.h"

PlayerController::PlayerController(Player* player) : m_player(player), m_healthBar(sf::Vector2f(20, 20), 200, this, Health), m_manaBar(sf::Vector2f(20, 45), 200, this, Mana)
{
	m_health = 50.0f;
	m_maxHealth = 100.0f;
}

PlayerController::~PlayerController()
{
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

void PlayerController::update(double &elapsed)
{
	if (m_mana < m_maxMana)
	{
		m_mana += m_manaRegen * elapsed;
	}

	m_healthBar.update();
	m_manaBar.update();
}

void PlayerController::draw(sf::RenderWindow& window)
{
	m_healthBar.draw(window);
	m_manaBar.draw(window);
}
