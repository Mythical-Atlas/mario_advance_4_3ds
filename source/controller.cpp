#include "controller.hpp"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

void Controller::handleEvent(union SDL_Event* event) {
    switch(event->type) {
        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
                case SDLK_LEFT: left = true; break;
                case SDLK_RIGHT: right = true; break;
                case SDLK_UP: up = true; break;
                case SDLK_DOWN: down = true; break;
                case SDLK_x: a = true; break;
                case SDLK_z: b = true; break;
                case SDLK_s: r = true; break;
                case SDLK_a: l = true; break;
                case SDLK_RETURN: start = true; break;
                case SDLK_LSHIFT: select = true; break;
            }
            break;
        case SDL_KEYUP:
            switch(event->key.keysym.sym) {
                case SDLK_LEFT: left = false; break;
                case SDLK_RIGHT: right = false; break;
                case SDLK_UP: up = false; break;
                case SDLK_DOWN: down = false; break;
                case SDLK_x: a = false; break;
                case SDLK_z: b = false; break;
                case SDLK_s: r = false; break;
                case SDLK_a: l = false; break;
                case SDLK_RETURN: start = false; break;
                case SDLK_LSHIFT: select = false; break;
            }
            break;
    }
}