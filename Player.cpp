#include "Player.h"

//There's lots of hard-coded values in this file which I intend to address after I've added a bit more functionality

Player::Player(sf::Texture &tex, double &elapsed) : idleAnim(*this), crouchAnim(*this), attackAnim(*this),runAnim(*this), 
														jumpAnim(*this), elapsed(elapsed), bIsFacingLeft(false), state(idle), 
															m_feetBox(0, 0, 35, 10), m_speed(200.0f), m_inputHandler(this),
																jumpHeight(300.0f), maxFallSpeed(450.0f), m_body(0, 0, 35, 60), m_controller(this)
{
	this->setTexture(tex);
	initializeAnims();

	//TODO: actually calculate this
	m_spriteSize = sf::Vector2f(136, 96);

	this->setOrigin(m_spriteSize.x / 2, m_spriteSize.y / 2);

	//m_rect.setOrigin(20, 34);
	m_rect.setSize(sf::Vector2f(m_feetBox.width, m_feetBox.height));
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(1.0f);
	m_rect.setFillColor(sf::Color::Transparent);
	
}

Player::~Player()
{
}

void Player::update()
{
	m_inputHandler.handleInput();
	handleDirection();

	m_controller.update(elapsed);

	switch (state)
	{
	case dying:
		//update anim until specific frame or time passed, then change to dead
		break;
	case dead:
		//deliberately empty; dead people can't act!
		break;
	case idle:
		idleAnim.update(elapsed);
		break;
	case moving:
		runAnim.update(elapsed);
		break;
	case jumping:
		this->move(0, -(fDeltaY * elapsed));

		if (fDeltaY > -maxFallSpeed)
			fDeltaY -= maxFallSpeed * elapsed;
		else
			fDeltaY = -maxFallSpeed;

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

	if (bIsTouchingFloor)
	{
		if (state == jumping) 
		{
			state = idle;
			fDeltaY = -50;
		}
	}

	if (!bIsTouchingFloor && state != dead)
	{
		state = jumping;
	}

	m_feetBox.left = this->getPosition().x - 17.5f;
	m_feetBox.top = this->getPosition().y + 18;

	m_body.left = this->getPosition().x - 15;
	m_body.top = this->getPosition().y - 35;

	m_rect.setPosition(sf::Vector2f(m_feetBox.left, m_feetBox.top));

	if (this->getPosition().y > Helpers::SCREEN_HEIGHT)
		this->setPosition(this->getPosition().x, 0);
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(*this);
	m_controller.draw(window);
}

#pragma region Getters + Setters


void Player::setIsTouchingFloor(bool val)
{
	this->bIsTouchingFloor = val;
}

float Player::getDeltaY() const
{
	return fDeltaY;
}

PlayerController* Player::getController()
{
	return &m_controller;
}

sf::Rect<int> Player::getBody() const
{
	return m_body;
}

State Player::getState() const
{
	return state;
}

void Player::setState(State s)
{
	state = s;
}

#pragma endregion


void Player::handleDirection()
{
	if (!bIsFacingLeft) {
		this->setScale(1, 1);
	}
	else {
		this->setScale(-1, 1);
	}
}

#pragma region Input + Actions


void Player::moveLeft()
{
	if (state != crouching && state != attacking)
	{
		this->move(-m_speed * elapsed, 0);
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
		this->move(m_speed * elapsed, 0);
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
		bIsTouchingFloor = false;
		state = jumping;
		fDeltaY = jumpHeight;
	}
}

#pragma endregion

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
