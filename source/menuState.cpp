#include <string>
#include <iostream>

#include "menuState.hpp"

using namespace std;

void MenuState::load()  {
	//tex.load("C:/Users/Ben/Desktop/Storage/2-18-2023 Desktop Clean/Laptop 3-2-2021/Ben Correll/Desktop/Storage/SPRING.png");
    
    tex.load("resources/test.png");
    sprite.init(&tex, new vec2[2]{vec2(0, 0), vec2(1, 1)});

	rp = RenderProgram("Sprite Program");
    rp.attachShader(GL_VERTEX_SHADER, "resources/spriteShader.vert");
    rp.attachShader(GL_FRAGMENT_SHADER, "resources/spriteShader.frag");
    rp.link();

	float data[16] = {
        0, 0, 0, 0,
        0, (float)tex.size[1], 0, 1,
        (float)tex.size[0], 0, 1, 0,
        (float)tex.size[0], (float)tex.size[1], 1, 1
    };
	int spriteAttribSizes[] = {4};

    rb = RenderBuffer(1, spriteAttribSizes, 16, data);

    AudioStream music("romfs/shortMusic.raw", SDL_MIX_MAXVOLUME, true);
	AudioStream grow("romfs/grow.raw", SDL_MIX_MAXVOLUME, false);
	AudioStream coin("romfs/coin.raw", SDL_MIX_MAXVOLUME, false);
}
void MenuState::init(Window* window, Game* game)  {
    cam.init(new int[2]{(int)window->getScreenSize().x, (int)window->getScreenSize().y});

    mixer.init();
    memset(&controller, 0, sizeof(Controller)); // could be done with a union in Controller

	audio.addStream(&music);
	audio.addStream(&grow);
	audio.addStream(&coin);
}
void MenuState::update(Window* window, Game* game)  {
    sprite.pos.x += 0.01f;
    sprite.pos.y += 0.01f;
}
void MenuState::render(Window* window, Game* game)  {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rp.useViewMatrix(&cam);

    sprite.render(&rp, &rb);
}
void MenuState::unload() {
	mixer.unload();
}

void MenuState::handleEvent(SDL_Event* event) {
    switch(event->type) {
        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
                case SDLK_LEFT: controller.left = true; break;
                case SDLK_RIGHT: controller.right = true; break;
                case SDLK_UP: controller.up = true; break;
                case SDLK_DOWN: controller.down = true; break;
            }
            break;
        case SDL_KEYUP:
            switch(event->key.keysym.sym) {
                case SDLK_LEFT: controller.left = false; break;
                case SDLK_RIGHT: controller.right = false; break;
                case SDLK_UP: controller.up = false; break;
                case SDLK_DOWN: controller.down = false; break;
            }
            break;
    }
}