#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

#include "Animation.h"
#include "Helpers.h"
#include "PlayerController.h"
#include "InputHandler.h"
#include "Character.h"

class Player : public Character
{
//Methods
public:
	Player(sf::Texture &tex, double &elapsed);
	~Player();

	void update() override;
	void draw(sf::RenderWindow & window);

	PlayerController* getController() override;

private:

	void initializeAnims();
	
//variables

private:

	Animation idleAnim;
	Animation attackAnim;
	Animation runAnim;
	Animation crouchAnim;
	Animation jumpAnim;

	//Passing this for the animations -- update() frequency should be controlled by Game::update()
	double &elapsed;
	

	sf::Vector2f m_spriteSize;

	InputHandler m_inputHandler;
	PlayerController m_controller;

	

public:

	//TODO: Make some getters
	sf::Rect<int> m_feetBox;
	sf::RectangleShape m_rect;

};

