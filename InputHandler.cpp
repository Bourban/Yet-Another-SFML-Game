#include "InputHandler.h"

#include "Player.h"


InputHandler::~InputHandler()
{
}


InputHandler::InputHandler(Player* owner) : m_owner(owner)
{
}



void InputHandler::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_owner->crouch();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_owner->moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_owner->moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		m_owner->attack();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		m_owner->modifyHealth(1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !bIsPressingKey)
	{
		m_owner->jump();
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

	if (!Helpers::isAnyRelevantKeyPressed() && m_owner->getState() != jumping)
	{
		m_owner->setState(idle);
	}

}
