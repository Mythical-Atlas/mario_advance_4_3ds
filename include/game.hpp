#ifndef GAME_H
#define GAME_H

#define STATE_COUNT 2

class State {
public:
	virtual void load() {}
	virtual void init(class Window* window, class Game* game) {}
	virtual void update(class Window* window, class Game* game) {}
	virtual void render(class Window* window, class Game* game) {}
	virtual void unload() {}
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
};

#endif