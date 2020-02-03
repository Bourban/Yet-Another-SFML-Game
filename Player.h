#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

#include "Animation.h"
#include "Helpers.h"
#include "HealthBar.h"

//State machine to handle animations and control when certain actions can be taken
//Should probably name states like STATE_IDLE etc.
enum State {idle, moving, jumping, attacking, crouching, dying, dead};

class Player : public sf::Sprite
{

//Methods
public:
	Player(sf::Texture &tex, double &elapsed);
	~Player();

	void update();
	//Draw method to draw subcomponents without having to do things like "p_player->getHealthBar()->draw(window);" in every screen
	void draw(sf::RenderWindow & window);

	void setIsTouchingFloor(bool val);

	float getDeltaY() const;
	float getHealth() const;
	float getMaxHealth() const;

	void modifyHealth(float change);

private:
	virtual void initializeAnims();

	void handleDirection();
	void handleInput();

	void moveLeft();
	void moveRight();
	void attack();
	void crouch();
	void jump();

//variables

private:
	State state;

	Animation idleAnim;
	Animation attackAnim;
	Animation runAnim;
	Animation crouchAnim;
	Animation jumpAnim;

	bool bIsTouchingFloor;
	bool bIsFacingLeft;
	bool bIsPressingKey;

	//Handled by state instead ?
	//bool bIsAlive;

	//Passing this for the animations -- update() frequency should be controlled by Game::update()
	double &elapsed;
	float fDeltaY;

	sf::Vector2f m_spriteSize;

	HealthBar m_healthBar;

	//Player stats
	float m_speed;
	float jumpHeight;
	float maxFallSpeed;

	float m_health;
	float m_maxHealth;

public:

	//TODO: Make some getters
	sf::Rect<int> m_feetBox;
	sf::RectangleShape m_rect;

};

