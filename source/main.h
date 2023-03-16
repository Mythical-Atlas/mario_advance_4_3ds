#ifndef MAIN_H
#define MAIN_H

#define STATE_COUNT 2
#define CAM_COUNT 1

#define STATE_TYPE_EMPTY 0
#define STATE_TYPE_MENU 1
#define STATE_TYPE_LEVEL 2

#include <iostream>
#include <string>

using namespace std;

// use CLASSES

struct TimeObj { // all times measured in ms
	uint64_t programStartTime;
	uint64_t frameStartTime;
	uint16_t lastFrameDuration;
};

struct MenuObj {
	string items[4] = {"start", "options", "help", "exit"};
	string* selection;
	
	int x;

	void load() {}

	void init() {x = 1;}

	void update(struct GameObj* game);

	void render(struct GameObj* game) {}

	void unload() {}
};

struct LevelObj {
	int tiles[5] = {122, 12, 54, 92, 213};
	int entities[2] = {4, 9};

	int y;

	// music
	// entities
	// objects
	// tilemap

	void load() {}

	void init() {y = 3;}

	void update(struct GameObj* game);

	void render(struct GameObj* game) {}

	void unload() {}
};

struct StateObj {
	void* objPtr;
	uint8_t type;

	void (*load)();

	void (*init)();

	void (*update)(struct GameObj*);

	void (*render)(struct GameObj*);

	void (*unload)();

	void create(int8_t type = -1) {
		if(type != -1) {this->type = type;}

		switch(this->type) {
			case STATE_TYPE_EMPTY:
				objPtr = 0;
				break;
			case STATE_TYPE_MENU:
				objPtr = new MenuObj;
				load = ((MenuObj*)objPtr)->load;
				break;
			case STATE_TYPE_LEVEL:
				objPtr = new LevelObj;
				break;
		}
	}
};

struct CamObj {
	// position
};

struct GameObj {
	bool running;
	TimeObj time;
	StateObj states[STATE_COUNT];
	StateObj* state;
	CamObj cams[CAM_COUNT];
	CamObj* cam;

	void changeState(int state) {
		if(this->state != nullptr) {this->state->unload();}

		this->state = &states[state];

		this->state->load();
		this->state->init();
	}
};

#endif