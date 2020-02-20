#pragma once
#include "Character.h"
#include "Animation.h"

class AnimatedCharacter : public Character
{
	//Methods
public:
	AnimatedCharacter(double &elapsed, sf::Texture &tex);
	~AnimatedCharacter();

	void update() override;

protected:
	//All the code in this function is tied to the sprite used, there is no catch-all
	//implementation for this (unless you standardise your sprite sheets)
	virtual void initialiseAnims() = 0;

	//Variables

public:


protected:

	Animation idleAnim;
	Animation attackAnim;
	Animation runAnim;
	Animation crouchAnim;
	Animation jumpAnim;

};

