#include "Terrain.h"

// basic terrain class
Terrain::Terrain(Texture* texture, Vector2f position, Vector2f size) :
	Entity(texture, position, size) {
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

Terrain::~Terrain() {}

// if we can specify texture at this level, this constructor much more useful
Frec::Frec(Texture* texture, Vector2f position, Vector2f size) : 
	Terrain(texture, position, size) {
}

Frec::~Frec() {}

Finish::Finish(Texture* texture, Vector2f position, Vector2f size) :
	Terrain(texture, position, size) {}