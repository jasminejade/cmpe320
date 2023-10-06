#include "Animation.h"


Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	totalTime = 0.0f;
	currentImage.x = 0; // start animation at 0

	uvRect.width = texture->getSize().x / float(imageCount.x); // need to cast to float bc un
	uvRect.height = texture->getSize().y / float(imageCount.y);

}

Animation::~Animation() {

}

void Animation::update(int row, float dt, bool faceRight) {
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (!faceRight) {
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);

	}
	else {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width); // change width of image to 													// negative version of the width to reflect and change direction
		uvRect.width = -abs(uvRect.width); 
	}
}
