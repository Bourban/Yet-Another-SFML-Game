#include "Player.h"

//There's lots of hard-coded values in this file which I intend to address after I've added a bit more functionality

Player::Player(sf::Texture &tex, double &elapsed) : idleAnim(*this), crouchAnim(*this), attackAnim(*this),runAnim(*this), 
														jumpAnim(*this), elapsed(elapsed), bIsFacingLeft(false), state(idle), 
															m_feetBox(0, 0, 35, 10), bIsPressingKey(false), m_speed(200.0f),
																jumpHeight(300.0f), maxFallSpeed(450.0f), m_maxHealth(100.0f), 
																	m_health(50.0f), m_healthBar(sf::Vector2f(20, 20), 200, this)
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

	if (!bIsTouchingFloor)
	{
		state = jumping;
	}

	
	m_feetBox.left = this->getPosition().x - 17.5f;
	m_feetBox.top = this->getPosition().y + 18;

	m_rect.setPosition(sf::Vector2f(m_feetBox.left, m_feetBox.top));

	if (this->getPosition().y > Helpers::SCREEN_HEIGHT)
		this->setPosition(this->getPosition().x, 0);

	m_healthBar.update();
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(*this);
	m_healthBar.draw(window);
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

float Player::getHealth() const
{
	return m_health;
}

float Player::getMaxHealth() const
{
	return m_maxHealth;
}

HealthBar* Player::getHealthBar()
{
	return &m_healthBar;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !bIsPressingKey)
	{
		jump();
		bIsPressingKey = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !bIsPressingKey) 
	{
		Helpers::bDebugMode = !Helpers::bDebugMode;
		bIsPressingKey = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		bIsPressingKey = false;
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

void Player::modifyHealth(float change)
{
	m_health += change;
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
