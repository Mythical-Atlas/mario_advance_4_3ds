#include "main.hpp"

// 3ds: osGetTime();
// pc: ???

void MenuState::update(GameObject* game)  {
	cout << "> ";
	string command;
	getline(cin, command);
	if(command == "exit") {game->running = false;}
	if(command == "level") {game->changeState(1);}
	if(command == "x") {cout << x << endl;}
	if(command == "x1") {x = 1;}
	if(command == "x2") {x = 2;}
}

void LevelState::update(GameObject* game)  {
	cout << ") ";
	string command;
	getline(cin, command);
	if(command == "exit") {game->running = false;}
	if(command == "menu") {game->changeState(0);}
	if(command == "y") {cout << y << endl;}
	if(command == "y3") {y = 3;}
	if(command == "y4") {y = 4;}
}

int main() {
	GameObject game;

	game.init();

	while(game.running) {
		game.state->update(&game);
		game.state->render(&game);
	}

	system("pause");
}