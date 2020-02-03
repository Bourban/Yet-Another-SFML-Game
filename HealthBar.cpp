#include "HealthBar.h"
#include "Player.h"

HealthBar::HealthBar(sf::Vector2f pos, float w, Player* owner) : m_pos(pos), m_owner(owner), bg(sf::Vector2f(w + 4, 20)), bar(sf::Vector2f(w, 20))
{
	bg.setPosition(pos.x - 2, pos.y);
	bar.setPosition(pos);

	bg.setFillColor(sf::Color(0, 0, 0, 155));
	bg.setOutlineColor(sf::Color::Black);
	bg.setOutlineThickness(1.f);
	bar.setFillColor(sf::Color::Red);

}


HealthBar::~HealthBar()
{
}

void HealthBar::update()
{
	bar.setScale(sf::Vector2f((m_owner->getHealth() / m_owner->getMaxHealth()), 1));
}

void HealthBar::draw(sf::RenderWindow & window)
{
	window.draw(bg);
	window.draw(bar);
}
