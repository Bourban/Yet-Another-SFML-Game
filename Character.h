#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum State { idle, moving, jumping, attacking, crouching, dying, dead };

class Character : sf::Transformable
{
	//Methods
public:
	Character(double elapsed);
	virtual ~Character() = 0;

	virtual void initialise() = 0;

	virtual void update();
	void draw(sf::RenderWindow& window);

	float getDeltaY() const;

	//maybe command pattern?

	void moveLeft();
	void moveRight();
	void attack();
	void crouch();
	void jump();

	void setIsTouchingFloor(bool val);
	sf::Rect<int> getBody() const;
	sf::Rect<int> getFeet() const;
	State getState() const;
	void setState(State s);

protected:

	void handleDirection();
	void handleSpriteAndBoxes();

	//Variables:
public:


protected:
	State state;

	sf::Sprite m_sprite;

	bool bIsTouchingFloor;
	bool bIsFacingLeft;

	double &elapsed;
	float fDeltaY;

	float m_speed;
	float jumpHeight;
	float maxFallSpeed;

	sf::Rect<int> m_body;
	sf::Rect<int> m_feetBox;
};
