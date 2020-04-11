#pragma once

#include <SFML/Graphics/Sprite.hpp>

class CharacterController;

enum State { idle, moving, jumping, attacking, crouching, dying, dead };

class Character : public sf::Transformable
{
public:
	Character();
	~Character() = 0;

	virtual void update();

	void setIsTouchingFloor(bool val);
	float getDeltaY() const;

	State getState() const;
	void setState(State s);

	sf::Rect<int> getBody() const;
	virtual CharacterController* getController();

	void moveLeft();
	void moveRight();
	void attack();
	void crouch();
	void jump();

protected:

	void handleDirection();

	//Members

public:

protected:

	State state = idle;

	sf::Sprite m_sprite;

	sf::Vector2f m_spriteSize;

	bool bIsTouchingFloor;
	bool bIsFacingLeft = false;

	float fDeltaY;

	float m_speed = 3.5f;
	float jumpHeight = 300.0f;
	float maxFallSpeed = 450.0f;

	sf::Rect<int> m_body;
};

