#pragma once

#include <SFML/Graphics/RenderWindow.hpp>


class Screen 
{
public :

	//return -1 from any screen to close the game
	virtual int run(sf::RenderWindow & window) = 0;
	
};