#include "BGSprite.h"
#include <SFML/Graphics/Texture.hpp>

BGSprite::BGSprite(sf::Texture & tex, sf::Vector2f pos, sf::Vector2f scale)
{
	
	this->setTexture(tex);

	this->setOrigin(sf::Vector2f(tex.getSize().x / 2, tex.getSize().y / 2));
	this->setPosition(pos);
	this->setScale(scale);
}

BGSprite::BGSprite(sf::Texture & tex, sf::IntRect rect, sf::Vector2f pos, sf::Vector2f scale)
{
	this->setTexture(tex);
	this->setTextureRect(rect);
	this->setPosition(pos);
	this->setScale(scale);
}

BGSprite::~BGSprite()
{
}
