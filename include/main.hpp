#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#include "graphics.hpp"
#include "collision.hpp"
#include "menuState.hpp"

#define STATE_TYPE_EMPTY 0
#define STATE_TYPE_MENU 1
#define STATE_TYPE_LEVEL 2

/*class TimeObject { // all times measured in ms
public:
	uint64_t programStartTime;
	uint64_t frameStartTime;
	uint16_t lastFrameDuration;
};*/

class Tileset {
	Texture tilesheet;
	int tileSize[2];
	CollisionShape* collisions;
};

class Tilemap {
	Tileset* tileset;
	int* tiles;
};

class Object {
	// vector position

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}
};

#endif