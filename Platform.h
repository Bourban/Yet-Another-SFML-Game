#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

class Platform : public sf::Sprite
{

public:
	Platform(sf::Texture &tex);
	Platform(sf::Texture &tex, int x, int y);
	~Platform();

	sf::IntRect getRect() const;
	sf::IntRect getTop() const;
	sf::RectangleShape pls;

private:

	sf::IntRect top;
	sf::IntRect rect;

};

