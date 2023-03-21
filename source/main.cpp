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
	//game.init(&window);

	AudioMixer audio;
	audio.init();

	AudioStream music("romfs/shortMusic.raw", SDL_MIX_MAXVOLUME, true);
	AudioStream grow("romfs/grow.raw", SDL_MIX_MAXVOLUME, false);
	AudioStream coin("romfs/coin.raw", SDL_MIX_MAXVOLUME, false);

	audio.addStream(&music);
	audio.addStream(&grow);
	audio.addStream(&coin);

	music.start();

	uint16_t audioCount = 0;

	while(game.running) {
		/*game.update();
		game.render();*/

		audioCount++;
		if(audioCount == 60) {music.start();}
		if(audioCount == 120) {music.pause();}
		if(audioCount == 200) {grow.start();}
		if(audioCount == 120) {music.resume();}

		if(audioCount % 2 == 0) {coin.start();}

		window.swap();
		SDL_Event event;
		while(window.pollEvent(&event)) {
			switch(event.type) {
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