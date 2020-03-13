#pragma once

#include<SFML/Graphics/Rect.hpp>
#include<SFML/Graphics/Sprite.hpp>

class PlayerController;

enum Type {gold, health, objective};

class Pickup : public sf::Sprite
{
public:
	Pickup(sf::Vector2f pos, sf::Texture &tex, Type type = health, float amount = 20.0f);
	virtual ~Pickup();

	sf::Rect<int> getRect();

	void onPickup(PlayerController* other);

private:
	sf::Rect<int> m_rect;

	Type m_type;
	float m_value;

};

