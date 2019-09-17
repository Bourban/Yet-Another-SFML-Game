#include "Platform.h"
#include <SFML\Graphics\Texture.hpp>


Platform::Platform(sf::Texture & tex)
{
	this->setTexture(tex);

}


Platform::Platform(sf::Texture & tex, int x, int y)
{
	this->setTexture(tex);
	this->setPosition(x, y);

	rect.height = tex.getSize().y;
	rect.width = tex.getSize().x;
	rect.top = x;
	rect.left = y;

	pls.setPosition(x, y);
	pls.setSize(sf::Vector2f(rect.width, rect.height));
}

Platform::~Platform()
{
}

sf::IntRect & Platform::getRect()
{
	return rect;
}
