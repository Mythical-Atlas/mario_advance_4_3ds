#include <string>
#include <iostream>

#include "levelState.hpp"

using namespace std;

void LevelState::update(Window* window, Game* game)  {
	cout << ") ";
	string command;
	getline(cin, command);
	if(command == "exit") {game->running = false;}
	if(command == "menu") {game->changeState(0);}
	if(command == "y") {cout << y << endl;}
	if(command == "y3") {y = 3;}
	if(command == "y4") {y = 4;}
}