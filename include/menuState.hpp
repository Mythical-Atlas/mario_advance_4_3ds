#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "game.hpp"
#include "graphics.hpp"
#include "renderProgram.hpp"
#include "renderBuffer.hpp"
#include "camera.hpp"
#include "window.hpp"
#include "audio.hpp"

class MenuState: public State {
public:
	RenderProgram rp;
	RenderBuffer rb;
	Camera cam;
	Controller controller;
	AudioMixer mixer;

	Texture tex;

	AudioStream music;
	AudioStream jump;
	AudioStream coin;
	AudioStream death;

	Sprite sprite;

	void load();
	void init(class Window* window, class Game* game);
	void update(Window* window, Game* game);
	void render(Window* window, Game* game);
	void unload();

	void handleEvent(SDL_Event* event);
};

#endif