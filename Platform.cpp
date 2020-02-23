#include "Platform.h"
#include <SFML\Graphics\Texture.hpp>


Platform::Platform(sf::Texture & tex)
{
	this->setTexture(tex);
}

Platform::Platform(sf::Texture & tex, int x, int y) : sf::Sprite(tex), rect(x, y, tex.getSize().x, tex.getSize().y), 
																				top(x, y, tex.getSize().x, tex.getSize().y * 0.25f)
{
	this->setPosition(x, y);

	pls.setPosition(rect.left, rect.top);
	pls.setSize(sf::Vector2f(rect.width, rect.height * 0.25f));

	pls.setFillColor(sf::Color::Transparent);
	pls.setOutlineThickness(1.0f);
	pls.setOutlineColor(sf::Color::Black);
}

Platform::Platform(sf::Texture & tex, int x, int y, sf::Vector2f scale) : sf::Sprite(tex), rect(x, y, tex.getSize().x * scale.x, tex.getSize().y * scale.y),
		top(x, y, tex.getSize().x * scale.x, (tex.getSize().y * scale.y) * 0.25f)
{
		this->setPosition(x, y);

		this->setScale(scale);

		pls.setPosition(rect.left, rect.top);
		pls.setSize(sf::Vector2f(rect.width, rect.height * 0.25f));

		pls.setFillColor(sf::Color::Transparent);
		pls.setOutlineThickness(1.0f);
		pls.setOutlineColor(sf::Color::Black);
}

Platform::~Platform()
{
}

sf::IntRect Platform::getRect() const
{
	return rect;
}

sf::IntRect Platform::getTop() const
{
	return top;
}
