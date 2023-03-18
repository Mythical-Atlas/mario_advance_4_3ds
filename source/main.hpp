#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#include "graphics.hpp"
#include "collision.hpp"

#define STATE_COUNT 2
#define CAM_COUNT 1

#define STATE_TYPE_EMPTY 0
#define STATE_TYPE_MENU 1
#define STATE_TYPE_LEVEL 2

class TimeObject { // all times measured in ms
public:
	uint64_t programStartTime;
	uint64_t frameStartTime;
	uint16_t lastFrameDuration;
};

class State {
public:
	virtual void load() {}
	virtual void init() {}
	virtual void update(struct GameObject* game) {}
	virtual void render(struct GameObject* game) {}
	virtual void unload() {}
};

class MenuState: public State {
public:
	int x;

	void load() {}
	void init() {x = 1;}
	void update(struct GameObject* game);
	void render(struct GameObject* game) {}
	void unload() {}
};

class LevelState: public State {
public:
	int y;

	// music
	// entities
	// objects
	// tilemap

	void load() {}
	void init() {y = 3;}
	void update(struct GameObject* game);
	void render(struct GameObject* game) {}
	void unload() {}
};

class GameObject {
public:
	bool running;
	State* states[STATE_COUNT];
	State* state;

	void init() {
		states[0] = new MenuState;
		states[1] = new LevelState;

		state = 0;

		changeState(0);
		running = true;
	}

	void changeState(int state) {
		if(this->state != nullptr) {this->state->unload();}

		this->state = states[state];

		this->state->load();
		this->state->init();
	}
};

class Tileset {
	Bitmap tilesheet;
	int tileSize[2];
	CollisionShape* collisions;
};

class Tile {
	//Tileset* tileset;
	int index[2];
};

class Tilemap {
	Tile* tiles;
};

class Object {
	// vector position

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}
};

class Controller {};

#endif