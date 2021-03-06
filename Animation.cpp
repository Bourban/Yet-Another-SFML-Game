#include "Animation.h"



Animation::Animation(sf::Sprite & target) : target(target)
{
	progress = 0.0;
	totalLength = 0.0;
}

Animation::~Animation()
{
}

void Animation::addFrame(Frame && frame)
{
	totalLength += frame.duration;
	frames.push_back(std::move(frame)); //using std::move eliminates the copy step from push_back
}

void Animation::update(double elapsed)
{
	progress += elapsed;
	double p = progress;
	for (size_t i = 0; i < frames.size(); i++) {
		p -= frames[i].duration;

		if (p > 0.0 && &(frames[i]) == &(frames.back())) {
			//set  i to -1 so the next loop sets it to 0, otherwise the first frame gets eaten!
			i = -1;
			continue;
		}

		if (p <= 0.0 || &(frames[i]) == &frames.back()) {
			target.setTextureRect(frames[i].rect);
			break;
		}
	}
}
