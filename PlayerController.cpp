#include "PlayerController.h"

#include "Player.h"

PlayerController::PlayerController(Player* player) : m_player(player), m_healthBar(sf::Vector2f(80, 20), 300, this, Health), m_manaBar(sf::Vector2f(80, 60), 300, this, Mana)
{
	m_health = 50.0f;
	m_maxHealth = 100.0f;
}

PlayerController::~PlayerController()
{
}

void PlayerController::addTexturesToBars(sf::Texture & bgTex, sf::Texture & barTexHealth, sf::Texture & barTexMana)
{
	m_healthBar.addTextures(bgTex, barTexHealth);
	m_manaBar.addTextures(bgTex, barTexMana);
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

		if (m_mana > m_maxMana)
		{
			m_mana = m_maxMana;
		}
	}

	m_healthBar.update();
	m_manaBar.update();
}

void PlayerController::draw(sf::RenderWindow& window)
{
	m_healthBar.draw(window);
	m_manaBar.draw(window);
}
