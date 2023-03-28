#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <chrono>

#include "game.hpp"
#include "graphics.hpp"
#include "renderProgram.hpp"
#include "renderBuffer.hpp"
#include "camera.hpp"
#include "window.hpp"
#include "audio.hpp"
#include "controller.hpp"

using namespace chrono;

class MenuState: public State {
public:
	time_point<steady_clock> stateStartTime;
	time_point<steady_clock> frameStartTime;

	uint32_t dt;
	uint32_t timeSinceInit;

	uint32_t ticksSinceLastDebugPrint;
	uint32_t debugPrintTimer;

	RenderProgram rp;
	RenderBuffer rb;
	Camera cam;
	Controller controller;
	AudioMixer mixer;

	Texture mmtopbgtex;
	Texture mmbotbgtex;
	Texture mmtexttex;

	Sprite mmtopbg;
	Sprite mmbotbg;
	Sprite mmstart;
	Sprite mmmap;
	Sprite mmsettings;
	Sprite mmexit;
	Sprite mmmario;
	Sprite mmluigi;

	AudioStream music;
	AudioStream move;
	AudioStream select;

	int menuIndex;
	int selectionIndex;

	bool moveReady;
	bool selectReady;

	void load();
	void init(class Window* window, class Game* game);
	void update(Window* window, Game* game);
	void render(Window* window, Game* game);
	void unload();

	void handleEvent(SDL_Event* event);
};

#endif