#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class CharacterController;

//could just be a boolean but I think this is a bit neater
enum OwnerTeam{Player, Enemy};

class Projectile :
	public sf::Sprite
{
public:
	Projectile(sf::Texture &tex, sf::Vector2f dir, float speed, float dam);
	Projectile(sf::Texture &tex, sf::Vector2f dir, float speed);
	~Projectile();

	void update();
	void draw(sf::RenderWindow &window);



private:
	//Re-refactor the player class to be able to use onHit on the base class which can be either enemy or player?
	void onHit(CharacterController &cc);

	//Members

public:

private:
	//defaults to player for constructors without a OwnerTeam
	OwnerTeam owner = Player;

	sf::Vector2f m_dir;
	float m_speed;

	float m_dam = 33.0f;

	sf::IntRect m_rect;

};

