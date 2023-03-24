#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H

#include "game.hpp"
#include "window.hpp"

class LevelState: public State {
public:
	int y;

	// music
	// entities
	// objects
	// tilemap

	void load() {}
	void init(class Window* window, class Game* game) {y = 3;}
	void update(Window* window, Game* game);
	void render(Window* window, Game* game) {}
	void unload() {}

	void handleEvent(SDL_Event* event) {}
};

#endif