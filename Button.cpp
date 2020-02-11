#include "Button.h"

#include <SFML/Graphics/Texture.hpp>

Button::Button()
{
}

Button::Button(sf::Texture & tex, sf::Vector2f pos) : m_sprite(tex), m_pos(pos), m_rect(pos.x, pos.y, tex.getSize().x, tex.getSize().y)
{
	//m_sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
	m_sprite.setPosition(pos);
}

Button::~Button()
{
}

bool Button::isPressed(sf::Vector2i point)
{
	if(m_rect.contains(point))
	{
		onPress();
		return true;
	}
	return false;
}

sf::Rect<int> Button::getRect()
{
	return m_rect;
}

void Button::onPress()
{
	//TODO
}

void Button::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
