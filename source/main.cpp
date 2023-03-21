#include <string>
#include <iostream>
#include <fstream>

#include "main.hpp"
#include "window.hpp"
#include "audio.hpp"

// 3ds: osGetTime();
// pc: ???

using namespace std;

int main(int argc, char* args[]) {
	Window window;
	window.init(false, 1280, 720, "TEST WINDOW");

	Game game;
	game.running = true;
	game.init(&window);

	AudioMixer audio;
	audio.init();

	AudioStream music("romfs/shortMusic.raw", SDL_MIX_MAXVOLUME, true);
	AudioStream grow("romfs/grow.raw", SDL_MIX_MAXVOLUME, false);
	AudioStream coin("romfs/coin.raw", SDL_MIX_MAXVOLUME, false);

	audio.addStream(&music);
	audio.addStream(&grow);
	audio.addStream(&coin);

	music.start();

	Controller controller;

	bool coinReady = false;

	while(game.running) {
		/*game.update();
		game.render();*/

		if(controller.up) {
			if(coinReady) {coin.start();}
			coinReady = false;
		}
		else {coinReady = true;}

		window.swap();
		SDL_Event event;
		while(window.pollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_LEFT: controller.left = true; break;
						case SDLK_RIGHT: controller.right = true; break;
						case SDLK_UP: controller.up = true; break;
						case SDLK_DOWN: controller.down = true; break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym) {
						case SDLK_LEFT: controller.left = false; break;
						case SDLK_RIGHT: controller.right = false; break;
						case SDLK_UP: controller.up = false; break;
						case SDLK_DOWN: controller.down = false; break;
					}
					break;
				case SDL_QUIT:
					game.running = false;
					break;
			}
		}
	}

	audio.unload();

	SDL_Quit();

	return 0;
}