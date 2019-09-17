#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "Animation.h"
#include "Helpers.h"

//State machine to handle animations and control when certain actions can be taken
enum State {idle, moving, jumping, attacking, crouching};

class Player : public sf::Sprite
{

//Methods
public:
	Player(sf::Texture &tex, double &elapsed);
	~Player();

	void update();

	//sf::Sprite inherits from sf::Drawable -- No draw method required

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

	double &elapsed;
	float fDeltaY;

	sf::Vector2f spriteSize;

};

