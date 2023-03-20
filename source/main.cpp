#include <string>
#include <iostream>

#include "main.hpp"
#include "window.hpp"

// 3ds: osGetTime();
// pc: ???

using namespace std;

int main(int argc, char* args[]) {
	Window window;
	window.init(false, 1280, 720, "TEST WINDOW");

	Game game;
	game.init(&window);

	while(game.running) {
		game.update();
		game.render();

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

	return 0;
}