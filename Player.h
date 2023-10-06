#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Animation.h"

using namespace sf;
using namespace std;

class BadInputException {
public:
	BadInputException(const string&);
	string& what();
private:
	string message;
};

// not sure if these are useful - dont worry they're not haha

// standard entity class for any object in the level
class Entity {
public:
	Entity(Texture* texture, Vector2f position, Vector2f size);
	~Entity();

	float getTop();
	float getLeft();
	float getRight();
	float getBottom();
	Vector2f getPosition() { return body.getPosition(); }

	int vCollide(Entity& other);
	int hCollide(Entity& other);

	void draw(RenderWindow& window);

protected:
	RectangleShape body;
	Sprite sprite;
};

// all entities that require movement capabilities, animation
class MovingEntity : public Entity {
public:
	MovingEntity(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, 
		float switchTime, float speed, bool faceRight);
	~MovingEntity();

	float getSpeed() { return speed; };

	void move(float dt, int speedMod, int dir);

protected:
	Vector2f movement, velocity;
	float speed, jump;
	bool faceRight;
	Animation animation;
	unsigned int image;
	bool isJumping;
	float floor;
};

// standard player class
class Player : public MovingEntity {
public:
	Player(Texture* texture, Vector2u imageCount, float switchTime, float speed, int health);
	~Player();

	int getHealth() { return health; }
	void update(float dt, vector<Entity*> items);
	//void jump(float yPos);

private:
	int health;
};

// base enemy class; should make subclasses for each specific enemy
class Enemy : public MovingEntity {
public:
	//Enemy Constructor which takes in "intelligence" and "health"
	Enemy(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime, float speed, string brain, int health);
	~Enemy();

	int getHealth();
	int healthDec();
	const string getIntelligence();

	void update(float dt, Vector2f playerPos, int wSize);
	void updateTemp(float dt);

private:
	int health;
	const string brain;
};