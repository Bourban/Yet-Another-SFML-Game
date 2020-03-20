#pragma once

#include <SFML/Graphics/Sprite.hpp>

//this class exists because I don't want to modify the SFML base class
//but it purely acts as a regular sf::Sprite with some extra constructors

class BGSprite : public sf::Sprite
{
public:
	BGSprite(sf::Texture &tex, sf::Vector2f pos, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
	BGSprite(sf::Texture &tex, sf::IntRect rect, sf::Vector2f pos, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
	~BGSprite();
};

