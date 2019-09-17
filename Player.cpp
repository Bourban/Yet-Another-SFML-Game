#include "Player.h"


Player::Player(sf::Texture &tex, double &elapsed) : idleAnim(*this), crouchAnim(*this), attackAnim(*this), runAnim(*this), jumpAnim(*this), elapsed(elapsed)
{
	this->setTexture(tex);
	initializeAnims();

	bIsFacingLeft = false;
	state = idle;

	spriteSize = sf::Vector2f(136, 96);

	this->setOrigin(spriteSize.x / 2, spriteSize.y / 2);
}


Player::~Player()
{
}

void Player::update()
{
	handleInput();
	handleDirection();

	switch (state)
	{
	case idle:
		idleAnim.update(elapsed);
		break;
	case moving:
		runAnim.update(elapsed);
		break;
	case jumping:
		this->move(0, -(fDeltaY * elapsed));

		if (fDeltaY > -450)
			fDeltaY -= 450 * elapsed;
		else
			fDeltaY = -450;

		jumpAnim.update(elapsed);
		break;
	case attacking:
		attackAnim.update(elapsed);
		break;
	case crouching:
		crouchAnim.update(elapsed);
		break;
	default:
		break;
	}

	if (this->getPosition().y > Helpers::GROUND_HEIGHT)
	{
		this->setPosition(this->getPosition().x, Helpers::GROUND_HEIGHT);

		if (state == jumping) 
		{
			state = idle;
			bIsTouchingFloor = true;
		}
	}

	if (this->getPosition().y != Helpers::GROUND_HEIGHT)
	{
		state = jumping;
		bIsTouchingFloor = false;
	}

}

void Player::handleDirection()
{
	if (!bIsFacingLeft) {
		this->setScale(1, 1);
	}
	else {
		this->setScale(-1, 1);
	}
}

void Player::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		crouch();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		attack();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jump();
	}

	if (!Helpers::isAnyRelevantKeyPressed() && state != jumping) 
	{
		state = idle;
	}
}

void Player::moveLeft()
{
	if (state != crouching && state != attacking)
	{
		this->move(-200 * elapsed, 0);
		bIsFacingLeft = true;

		if (state != jumping)
		{
			state = moving;
		}
	}
}

void Player::moveRight()
{
	if (state != crouching && state != attacking)
	{
		this->move(200 * elapsed, 0);
		bIsFacingLeft = false;

		if (state != jumping)
		{
			state = moving;
		}
	}
}

void Player::attack()
{
	if(state != jumping)
	state = attacking;
}

void Player::crouch()
{
	if (state != jumping)
	{
		state = crouching;
	}
}

void Player::jump()
{
	if (state == crouching)
	{
		state = idle;
		return;
	}
	if (state != jumping  && state != attacking)
	{
		state = jumping;
		fDeltaY = 300;
	}
}


void Player::initializeAnims()
{
	//TODO: Change all these to use spriteSize

	//Attack
	attackAnim.addFrame({ sf::IntRect(0,0,136,96) , 0.1667 });
	attackAnim.addFrame({ sf::IntRect(136,0,136,96) , 0.1667 });
	attackAnim.addFrame({ sf::IntRect(272,0,136,96) , 0.1667 });
	attackAnim.addFrame({ sf::IntRect(408,0,136,96) , 0.1667 });
	attackAnim.addFrame({ sf::IntRect(544,0,136,96) , 0.1667 });
	attackAnim.addFrame({ sf::IntRect(680,0,136,96) , 0.1667 });
	attackAnim.addFrame({ sf::IntRect(816,0,136,96) , 0.15 });

	//idle
	idleAnim.addFrame({ sf::IntRect(0,192,136,96) , 0.12 });
	idleAnim.addFrame({ sf::IntRect(136,192,136,96) , 0.12 });
	idleAnim.addFrame({ sf::IntRect(272,192,136,96) , 0.12 });
	idleAnim.addFrame({ sf::IntRect(408,192,136,96) , 0.12 });
	idleAnim.addFrame({ sf::IntRect(544,192,136,96) , 0.12 });
	idleAnim.addFrame({ sf::IntRect(680,192,136,96) , 0.12 });

	//running 
	runAnim.addFrame({ sf::IntRect(0, 288, 136, 96), 0.1 });
	runAnim.addFrame({ sf::IntRect(136, 288, 136, 96), 0.1 });
	runAnim.addFrame({ sf::IntRect(272, 288, 136, 96), 0.1 });
	runAnim.addFrame({ sf::IntRect(408, 288, 136, 96), 0.1 });
	runAnim.addFrame({ sf::IntRect(544, 288, 136, 96), 0.1 });
	runAnim.addFrame({ sf::IntRect(680, 288, 136, 96), 0.1 });
	runAnim.addFrame({ sf::IntRect(816, 288, 136, 96), 0.1 });
	runAnim.addFrame({ sf::IntRect(952, 288, 136, 96), 0.1 });

	//crouching
	crouchAnim.addFrame({ sf::IntRect(0, 96, 136, 96), 0.1 });
	crouchAnim.addFrame({ sf::IntRect(136, 96, 136, 96), 0.1 });
	crouchAnim.addFrame({ sf::IntRect(272, 96, 136, 96), 0.1 });
	crouchAnim.addFrame({ sf::IntRect(408, 96, 136, 96), 0.1 });
	crouchAnim.addFrame({ sf::IntRect(544, 96, 136, 96), 0.1 });
	crouchAnim.addFrame({ sf::IntRect(680, 96, 136, 96), 0.1 });

	//jumping
	jumpAnim.addFrame({sf::IntRect(1088, 192, 136, 96), 0.1});

}
