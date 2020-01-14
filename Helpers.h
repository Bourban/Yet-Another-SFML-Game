#pragma once

#include <SFML\Window\Keyboard.hpp>

namespace Helpers
{
	static const int GROUND_HEIGHT = 576;

	static const double MS_PER_UPDATE = 1000 / 60;

	static const int SCREEN_HEIGHT = 720;
	static const int SCREEN_WIDTH = 1280;


	extern bool bDebugMode;

	static bool isAnyKeyPressed()
	{
		for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
		{
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
				return true;
		}
		return false;
	}

	//Returns true if any bound keys are currently being pressed
	static bool isAnyRelevantKeyPressed()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			return true;

		return false;
	}

	static bool isAnyToggleableKeyPressed()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			return true;

		return false;
	}

	static bool isOverlapping(sf::IntRect &a, sf::IntRect &b)
	{
		return a.intersects(b);
	}
}