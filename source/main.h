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

class TimeObj { // all times measured in ms
public:
	uint64_t programStartTime;
	uint64_t frameStartTime;
	uint16_t lastFrameDuration;
};

class StateObj {
public:
	virtual void load() {}
	virtual void init() {}
	virtual void update(struct GameObj* game) {}
	virtual void render(struct GameObj* game) {}
	virtual void unload() {}
};

class MenuObj: public StateObj {
public:
	int x;

	void load() {}
	void init() {x = 1;}
	void update(struct GameObj* game);
	void render(struct GameObj* game) {}
	void unload() {}
};

class LevelObj: public StateObj {
public:
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

class CamObj {
	// position
};

class GameObj {
public:
	bool running;
	TimeObj time;
	StateObj* states[STATE_COUNT];
	StateObj* state;
	CamObj cams[CAM_COUNT];
	CamObj* cam;

	void init() {
		states[0] = new MenuObj;
		states[1] = new LevelObj;

		state = 0;
		cam = 0;

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

#endif