#pragma once
#include <SFML\Graphics.hpp>

/************************************************************************************

	Taken from https://github.com/SFML/SFML/wiki/Easy-Animations-With-Spritesheets
	and modified slightly by Jordan Walsh (Literally changed one character)

**************************************************************************************/

struct Frame {
	sf::IntRect rect;
	double duration;
};


class Animation
{
private:
	std::vector<Frame> frames;
	double totalLength;
	double progress;
	sf::Sprite &target;

public:
	Animation(sf::Sprite &target);
	virtual ~Animation();

	void addFrame(Frame&& frame);
	void update(double elapsed);
	const double getLength() const { return totalLength; }

};

