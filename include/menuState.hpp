#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "game.hpp"
#include "graphics.hpp"
#include "renderProgram.hpp"
#include "renderBuffer.hpp"
#include "camera.hpp"
#include "window.hpp"

class MenuState: public State {
public:
	Texture tex;
	Sprite sprite;
	RenderProgram rp;
	RenderBuffer rb;
	Camera cam;

	void load();
	void init(class Window* window, class Game* game);
	void update(Window* window, Game* game);
	void render(Window* window, Game* game);
	void unload();
};

#endif