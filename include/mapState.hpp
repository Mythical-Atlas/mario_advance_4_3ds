#ifndef MAP_STATE_H
#define MAP_STATE_H

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

class MapState: public State {
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

	Texture botbgtex;
	Texture maptex;
	Texture ferntex;
	Texture icontex;

	Sprite botbgsprite;
	Sprite mapsprite;
	Sprite fernsprite;
	Sprite iconsprite;

	AudioStream music;
	AudioStream move;
	AudioStream select;

	int mapIndex;

	bool moveReady;
	bool selectReady;
	
	int movingIcon;
	int iconDirection;

	uint32_t animTimer;
	int fernFrame;
	int iconFrame;

	void load();
	void init(class Window* window, class Game* game);
	void update(Window* window, Game* game);
	void render(Window* window, Game* game);
	void unload();

	void handleEvent(SDL_Event* event);
};

#endif