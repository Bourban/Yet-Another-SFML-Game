#include "Pickup.h"

#include "Player.h"
#include<SFML/Graphics/Texture.hpp>

#include <iostream>

Pickup::Pickup(sf::Vector2f pos, sf::Texture & tex, Type type, float value) : m_rect((sf::Vector2i)pos, (sf::Vector2i)tex.getSize()),
																m_type(type), m_value(value)
{
	this->setTexture(tex);
	this->setPosition(pos);
}

Pickup::~Pickup()
{
	std::cout << ":(\n";
}

sf::Rect<int> Pickup::getRect()
{
	return m_rect;
}

void Pickup::onPickup(Player* other)
{
	switch (m_type)
	{
	case gold:
		break;
	case health:
		other->modifyHealth(m_value);
		break;
	case objective:
		break;
	default:
		break;
	}

}
