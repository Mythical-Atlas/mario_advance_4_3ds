#ifndef GAME_H
#define GAME_H

//#include "audio.hpp"

#define STATE_COUNT 2

struct Controller { // TODO: input buffering
	bool left   : 1;
	bool right  : 1;
	bool up     : 1;
	bool down   : 1;
	bool a      : 1;
	bool b      : 1;
	bool l      : 1;
	bool r      : 1;
	bool start  : 1;
	bool select : 1;
};

class State {
public:
	virtual void load() {}
	virtual void init(class Window* window, class Game* game) {}
	virtual void update(class Window* window, class Game* game) {}
	virtual void render(class Window* window, class Game* game) {}
	virtual void unload() {}

	virtual void handleEvent(SDL_Event* event) {}
};

class Game {
public:
	bool running;
	State* states[STATE_COUNT];
	State* state;
	Window* window;
	
	void changeState(int state);

	void init(Window* window);
	void update();
	void render();

	void handleEvent(SDL_Event* event) {}
};

#endif