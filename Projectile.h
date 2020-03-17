#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class CharacterController;
class Character;

//could just be a boolean but I think this is a bit neater
enum OwnerTeam{PlayerTeam, EnemyTeam};

class Projectile :
	public sf::Sprite
{
public:
	Projectile(double& elapsed, sf::Texture &tex, sf::Vector2f dir, OwnerTeam team = PlayerTeam , float speed = 5.0f, float dam = 50);
	Projectile(double& elapsed, sf::Texture &tex, sf::Vector2f dir, OwnerTeam team = PlayerTeam, float speed = 5.0f, float dam = 50,  sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));

	~Projectile();

	OwnerTeam getOwner() const;

	void update();
	void draw(sf::RenderWindow &window);

	void checkCollision(Character &other);

private:
	//Re-refactor the player class to be able to use onHit on the base class which can be either enemy or player?
	void onHit(CharacterController &cc);

	void handleBox();

	/////////////////////////////
	//			Members		   //
	/////////////////////////////

public:

private:
	//defaults to player for constructors without a OwnerTeam
	OwnerTeam owner = PlayerTeam;

	sf::Vector2f m_dir;
	float m_speed;

	sf::Vector2f m_spriteSize;

	float m_dam = 33.0f;

	double& m_elapsed;

	sf::IntRect m_rect;

};

