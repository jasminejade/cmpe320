#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Animation {
public:
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float dt, bool faceRight);  // change in time to work the same on all computer
	IntRect uvRect; // used to store animation

private:
	Vector2u imageCount; // number of images we have
	Vector2u currentImage;

	float totalTime;
	float switchTime; // how long we want each time to take
};
