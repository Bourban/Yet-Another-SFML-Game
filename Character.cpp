#include "Character.h"

Character::Character(double elapsed) : elapsed(elapsed), maxFallSpeed(450.0f), m_speed(200.0f),
										jumpHeight(300.0f), state(idle), bIsFacingLeft(false)
{
}

Character::~Character()
{
}

void Character::initialise()
{
	//hoping GetGlobablBounds will get the height and width of the chosen rectangle
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2));

	//sprite should be created in constructor, this will be called afterwards
	m_body.height = m_sprite.getLocalBounds().height;
	m_body.width = m_sprite.getLocalBounds().width;

	m_feetBox.height = m_sprite.getLocalBounds().height / 10;
	m_feetBox.width = m_sprite.getLocalBounds().width;

}

void Character::update()
{
#pragma region State + Direction

	//TODO: Delete empty cases when all the funcitonality is implemented
	switch (state)
	{
	case dying:
		//update anim until specific frame or time passed, then change to dead
		break;
	case dead:
		//deliberately empty; dead people can't act!
		break;
	case idle:
		break;
	case moving:
		break;
	case jumping:
		this->move(0, -(fDeltaY * elapsed));

		if (fDeltaY > -maxFallSpeed)
			fDeltaY -= maxFallSpeed * elapsed;
		else
			fDeltaY = -maxFallSpeed;
		break;
	case attacking:
		break;
	case crouching:
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

#pragma endregion

	handleDirection();
	handleSpriteAndBoxes();

}

void Character::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Character::handleDirection()
{
	//Sprite's origin is set to centre, so this should effectively just flip the sprite on the Y axis
	if (!bIsFacingLeft) {
		m_sprite.setScale(1, 1);
	}
	else {
		m_sprite.setScale(-1, 1);
	}
}

void Character::handleSpriteAndBoxes()
{
	m_sprite.setPosition(this->getPosition() - sf::Vector2f(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2));

	m_body.left = this->getPosition().x;
	m_body.top = this->getPosition().y;

	m_feetBox.left = this->getPosition().x;
	m_feetBox.top = this->getPosition().y;
}

#pragma region Getters + Setters
void Character::setIsTouchingFloor(bool val)
{
	bIsTouchingFloor = val;
}

float Character::getDeltaY() const
{
	return fDeltaY;
}

State Character::getState() const
{
	return state;
}

void Character::setState(State s)
{
	state = s;
}

sf::Rect<int> Character::getBody() const
{
	return m_body;
}

sf::Rect<int> Character::getFeet() const
{
	return m_body;
}

#pragma endregion

#pragma region Actions

void Character::moveLeft()
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

void Character::moveRight()
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

void Character::attack()
{
	if (state != jumping)
	{
		state = attacking;
	}
}

void Character::crouch()
{
	if (state != jumping)
	{
		state = crouching;
	}
}

void Character::jump()
{
	if (state == crouching)
	{
		state = idle;
		return;
	}
	if (state != jumping && state != attacking)
	{
		bIsTouchingFloor = false;
		state = jumping;
		fDeltaY = jumpHeight;
	}
}

#pragma endregion

