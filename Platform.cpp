#include "Platform.h"
#include <SFML\Graphics\Texture.hpp>


Platform::Platform(sf::Texture & tex)
{
	this->setTexture(tex);
}

Platform::Platform(sf::Texture & tex, int x, int y) : sf::Sprite(tex)
{
	this->setPosition(x, y);

	rect.height = tex.getSize().y;
	rect.width = tex.getSize().x;
	rect.top = x;
	rect.left = y;

	pls.setPosition(x, y);
	pls.setSize(sf::Vector2f(rect.width, rect.height));

	pls.setFillColor(sf::Color::Transparent);
	pls.setOutlineThickness(1.0f);
	pls.setOutlineColor(sf::Color::Black);
}

Platform::~Platform()
{
}

sf::IntRect & Platform::getRect()
{
	return rect;
}
