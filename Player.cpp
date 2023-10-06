#include <cmath>
#include <iostream>

#include "Player.h"

BadInputException::BadInputException(const string& message) : message(message) {}
string& BadInputException::what() {
	return(message);
}

// Entity parent class: basic rectangular position and size of sprite setup
Entity::Entity(Texture* texture, Vector2f position, Vector2f size) {
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

Entity::~Entity() {

}

float Entity::getTop() {
	//cout << getPosition().y - body.getSize().y / 2.0f;
	return getPosition().y - body.getSize().y / 2.0f;
}

float Entity::getBottom() {
	return getPosition().y + body.getSize().y / 2.0f;
}

float Entity::getLeft() {
	return getPosition().x - body.getSize().x / 2.0f;
}

float Entity::getRight() {
	return getPosition().x + body.getSize().x / 2.0f;
}

int Entity::vCollide(Entity& other) {
	float topDist = abs(this->getPosition().y - other.getBottom());
	float bottomDist = abs(this->getPosition().y - other.getTop());
	float edge = body.getSize().y / 2.0f;
	// check distances
	if ((topDist <= edge || bottomDist <= edge) && (other.getPosition().x <= getRight() && other.getPosition().x >= getLeft())) {
		
		if (topDist > bottomDist) // other collides from the bottom
			return -1;
		else if (topDist < bottomDist) // other collides from the top
			return 1;
	}
	// does not collide
	return 0;
}

int Entity::hCollide(Entity& other) {
	float rightDist = abs(this->getPosition().x - other.getLeft());
	float leftDist = abs(this->getPosition().x - other.getRight());
	float edge = body.getSize().x / 2.0f;
	// check distances
	if ((leftDist <= edge || rightDist <= edge) && (other.getPosition().y <= getBottom() && other.getPosition().y >= getTop())) {

		if (leftDist > rightDist) // other collides on players right side
			return -1;
		else if (leftDist < rightDist) // other collides on players left side
			return 1;
	}
	// does not collide
	return 0;
}

void Entity::draw(RenderWindow& window) {
	window.draw(body);
}

// MovingEntity class
MovingEntity::MovingEntity(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount,
	float switchTime, float speed, bool faceRight) :
	Entity(texture, position, size), animation(texture, imageCount, switchTime) {
	this->speed = speed;
	this->faceRight = faceRight;
	this->floor = getBottom(); // absolute floor
}

MovingEntity::~MovingEntity() {

}

// general movement enabler for horizontal movement and jumping
void MovingEntity::move(float dt, int speedMod, int dir) {
	if (dir == -1) { // move left
		movement.x = -speed * dt;
		animation.update(image, dt * speedMod, false);
	}
	else if (dir == 1) { // move right
		movement.x = speed * dt;
		animation.update(image, dt * speedMod, true);
	}
	else
		movement.x = 0;
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	if (isJumping) { // gravity simulation
		movement.y += 6 * dt;
		if ((int)getBottom() >= floor) {
			movement.y = 0;
			isJumping = false;
		}
	}
}

// Player class
Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed, int health) : // initialzie list
	MovingEntity(texture, Vector2f(-2350.0f,720.0*0.3), Vector2f(100.0f,120.0f), imageCount, switchTime, speed, true) { // member variable calls default construtor
	this->health = health;
	velocity = Vector2f(0.0f, 0.0f);
	jump = 1000;
	isJumping = false;
}

Player::~Player() {

}

// checks key commands to enable movement
void Player::update(float dt, vector<Entity*> items) {
	int dir = 0;
	int vertical = 0;
	int horizontal = 0; // tracking collisions
	for (int i = 0; i < items.size(); i++) {
		int verticalTemp = vCollide(*items[i]); // check all nonplayer entities for collision
		int horizontalTemp = hCollide(*items[i]);
		if (verticalTemp != 0) {
			if (verticalTemp < 0) { // hit terrain from above
				isJumping = false;
				movement.y = 0;
			}
			else movement.y = -movement.y; // hit terrain from below
			vertical = verticalTemp;
		}
		if (horizontalTemp != 0) {
			movement.x = 0;
			horizontal = horizontalTemp;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && !isJumping) {
		isJumping = true;
		//movement.y = - jump * dt;
		movement.y = -1.5;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && horizontal != 1)
		dir = -1;
	else if (Keyboard::isKeyPressed(Keyboard::Right) && horizontal != -1)
		dir = 1;
	else if (Keyboard::isKeyPressed(Keyboard::Left) && horizontal == 1 ||
		Keyboard::isKeyPressed(Keyboard::Right) && horizontal == -1)
		dir = 0;
	if (vertical == 0 && (int)getBottom() < floor)
		isJumping = true;
	move(dt, 5, dir);
}
