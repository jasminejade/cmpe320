#include "Player.h"

// standard enemy class - maybe find a way to specify the texture at this level
Enemy::Enemy(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime, float speed, string smarts, int health):
	health(health), brain(smarts), MovingEntity(texture, position, size, imageCount, switchTime, speed, false) {
	isJumping = false;
	/*body.setSize(Vector2f(200.0f, 200.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(0.0f, 0.36 * 720.0);
	body.setTexture(texture);*/
}

Enemy::~Enemy() {

}

void Enemy::update(float dt, Vector2f playerPos, int wSize) {
	float distx = pow(playerPos.x - this->getPosition().x, 2);
	float disty = pow(playerPos.y - this->getPosition().y, 2);
	float distToPlayer = sqrt(distx + disty);
	if (distToPlayer < wSize / 2.0f + 100.0) {
		move(dt*1.3, 1, -1);
	}
}

// temp moving class for enemies for testing
void Enemy::updateTemp(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		move(dt, 1, -1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		move(dt, 1, 1);
	else
		move(dt, 1, 0);
}