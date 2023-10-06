#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "Player.h"
#include "Animation.h"

using namespace std;
using namespace sf;

class BadTerrainException : BadInputException {};

// all terrain will use this class, might not be needed depending on entity collision
// functionality
class Terrain : public Entity {
public:
	Terrain(Texture* texture, Vector2f position, Vector2f size);
	~Terrain();

private:
	bool sturdy;
};

// some random subclasses based on the images we have

class Platform : public Terrain {};

class Brick : public Terrain {};

class Crate : public Terrain {};

class Box : public Terrain {};

class Frec : public Terrain {
public:
	Frec(Texture* texture, Vector2f position, Vector2f size);
	~Frec();
};

class Finish : public Terrain {
public:
	Finish(Texture* texture, Vector2f position, Vector2f size);
};