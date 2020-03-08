#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::update()
{
	handleDirection();

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

	m_sprite.setPosition(this->getPosition());

}

void Character::handleDirection()
{
	if (!bIsFacingLeft) {
		this->setScale(1, 1);
		m_sprite.setScale(1, 1);
	}
	else {
		this->setScale(-1, 1);
		m_sprite.setScale(-1, 1);
	}
}

#pragma region Input + Actions


void Character::moveLeft()
{
	if (state != crouching && state != attacking)
	{
		this->move(-m_speed, 0);
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
		this->move(m_speed, 0);
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
		state = attacking;
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

#pragma region Getters + Setters

void Character::setIsTouchingFloor(bool val)
{
	this->bIsTouchingFloor = val;
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

#pragma endregion
