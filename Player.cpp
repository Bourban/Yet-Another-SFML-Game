#include "Player.h"

//There's lots of hard-coded values in this file which I intend to address after I've added a bit more functionality

Player::Player(sf::Texture &tex, double &elapsed) : idleAnim(m_sprite), crouchAnim(m_sprite), attackAnim(m_sprite),runAnim(m_sprite), 
														jumpAnim(m_sprite), elapsed(elapsed), m_feetBox(0, 0, 35, 10),m_inputHandler(this), 
															m_body(0, 0, 35, 60), m_controller(this)
{
	m_sprite.setTexture(tex);
	initializeAnims();

	//TODO: actually calculate this
	m_spriteSize = sf::Vector2f(136, 96);
	m_spriteSize = sf::Vector2f(136, 96);

	m_sprite.setOrigin(m_spriteSize.x / 2, m_spriteSize.y / 2);

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
	Character::update();

	m_inputHandler.handleInput();

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
	window.draw(m_sprite);
	m_controller.draw(window);
}

#pragma region Getters + Setters

PlayerController* Player::getController()
{
	return &m_controller;
}

sf::Rect<int> Player::getBody() const
{
	return m_body;
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
