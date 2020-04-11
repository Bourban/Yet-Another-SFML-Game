#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class PlayerController;

enum BarType{Health, Mana};

class HealthBar
{
public:
	//HealthBar();
	HealthBar(sf::Vector2f pos, float w, PlayerController* owner, BarType type);
	~HealthBar();

	void addTextures(sf::Texture& bgTex, sf::Texture& barTex);

	void update();
	//call this in after every other object's draw call in each screen's render()
	void draw(sf::RenderWindow& window);

private:

	BarType m_type;

	sf::RectangleShape bg;
	sf::RectangleShape bar;

	sf::Vector2f m_pos;

	PlayerController* m_owner;

	float width;
};

