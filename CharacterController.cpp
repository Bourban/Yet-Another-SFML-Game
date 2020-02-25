#include "CharacterController.h"



CharacterController::CharacterController() : m_mana(50.0f), m_maxMana(100.0f), m_manaRegen(5.0f)
{
}


CharacterController::~CharacterController()
{
}

float CharacterController::getHealth() const
{
	return m_health;
}

float CharacterController::getMaxHealth() const
{
	return m_maxHealth;
}

float CharacterController::getMana() const
{
	return m_mana;
}

float CharacterController::getMaxMana() const
{
	return m_maxMana;
}


