#include "game.hpp"
#include "menuState.hpp"
#include "levelState.hpp"

void Game::init() {
    states[0] = new MenuState;
    states[1] = new LevelState;

    state = nullptr;

    changeState(0);
    running = true;
}

void Game::changeState(int state) {
    if(this->state != nullptr) {this->state->unload();}

    this->state = states[state];

    this->state->load();
    this->state->init();
}