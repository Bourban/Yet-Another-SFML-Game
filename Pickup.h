#pragma once

#include<SFML/Graphics/Rect.hpp>
#include<SFML/Graphics/Sprite.hpp>

class Player;

enum Type {gold, health};

class Pickup : public sf::Sprite
{
public:
	Pickup(sf::Vector2f pos, sf::Texture &tex, Type type, float amount);
	virtual ~Pickup();

	sf::Rect<int> getRect();

	void onPickup(Player* other);

private:
	sf::Rect<int> m_rect;

	Type m_type;
	float m_value;

};

