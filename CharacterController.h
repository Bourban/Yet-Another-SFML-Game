#pragma once
class CharacterController
{
public:
	CharacterController();
	~CharacterController();

	float getHealth() const;
	float getMaxHealth() const;

	float getMana() const;
	float getMaxMana() const;

	virtual void modifyHealth(float change) = 0;

protected:

	//Members

public:

protected:

	float m_mana;
	float m_maxMana;

	float m_manaRegen;

	float m_health;
	float m_maxHealth;

};

