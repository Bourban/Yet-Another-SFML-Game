#pragma once

#include <SFML/Graphics/RenderWindow.hpp>


class Screen 
{
public :

	virtual int run(sf::RenderWindow & window) = 0;
	
};