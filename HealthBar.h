#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Player;

class HealthBar
{
public:
	//HealthBar();
	HealthBar(sf::Vector2f pos, float w, Player* owner);
	~HealthBar();

	void update();
	//call this in after every other object's draw call in each screen's render()
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape bg;
	sf::RectangleShape bar;

	sf::Vector2f m_pos;

	Player* m_owner;

	float width;
};
