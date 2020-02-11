#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

class Button
{
public:
	Button();
	Button(sf::Texture& tex, sf::Vector2f pos);
	~Button();

	bool isPressed(sf::Vector2i point);

	sf::Rect<int> getRect();

	void onPress();

	void draw(sf::RenderWindow& window);

private:
	sf::Rect<int> m_rect;
	sf::Sprite m_sprite;
	sf::Vector2f m_pos;
};

