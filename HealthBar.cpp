#include "HealthBar.h"
#include "PlayerController.h"

HealthBar::HealthBar(sf::Vector2f pos, float w, PlayerController* owner, BarType type) : m_pos(pos), m_owner(owner), bg(sf::Vector2f(w + 2, 22)), bar(sf::Vector2f(w, 20)),
m_type(type)
{
	bg.setPosition(pos.x - 1, pos.y - 1);
	bar.setPosition(pos);

	bg.setFillColor(sf::Color(0, 0, 0, 155));
	bg.setOutlineColor(sf::Color::Black);
	bg.setOutlineThickness(1.f);

	if (m_type == Health)
	{
		bar.setFillColor(sf::Color::Red);
	}
	else if(m_type == Mana)
	{
		bar.setFillColor(sf::Color::Blue);
	}
}


HealthBar::~HealthBar()
{
}

void HealthBar::update()
{
	if (m_type == Health)
	{
		bar.setScale(sf::Vector2f((m_owner->getHealth() / m_owner->getMaxHealth()), 1));
	}
	else if (m_type == Mana)
	{
		bar.setScale(sf::Vector2f((m_owner->getMana() / m_owner->getMaxMana()), 1));
	}
}

void HealthBar::draw(sf::RenderWindow & window)
{
	window.draw(bg);
	window.draw(bar);
}
