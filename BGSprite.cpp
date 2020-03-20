#include "BGSprite.h"


BGSprite::BGSprite(sf::Texture & tex, sf::Vector2f pos, sf::Vector2f scale)
{
	this->setTexture(tex);
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
