#include "AnimatedCharacter.h"

AnimatedCharacter::AnimatedCharacter(double & elapsed, sf::Texture &tex) : idleAnim(m_sprite), attackAnim(m_sprite), runAnim(m_sprite),
															crouchAnim(m_sprite), jumpAnim(m_sprite), Character(elapsed)
{
	
	m_sprite.setTexture(tex);

}

AnimatedCharacter::~AnimatedCharacter()
{
}

void AnimatedCharacter::update()
{
	Character::update();

	//This switch statement (not to be confused with the one from Character) simply handles
	//animations based on the character's state
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
}
