#ifndef OBJECTS_HOLDER_H
#define OBJECTS_HOLDER_H

#include "global.h"

#define MAX_OBJECTS 40

QuestionBlock questionBlocks[MAX_OBJECTS];
Coin coins[MAX_OBJECTS];
Goomba goombas[MAX_OBJECTS];
Mushroom mushrooms[MAX_OBJECTS];
Koopa koopas[MAX_OBJECTS];
Shell shells[MAX_OBJECTS];
Piranha piranhas[MAX_OBJECTS];
Particle particles[MAX_OBJECTS];
Feather feathers[MAX_OBJECTS];
BrickBlock brickBlocks[MAX_OBJECTS];
PipeEntrance pipeEntrances[MAX_OBJECTS];

int findFreeQuestionBlock() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!questionBlocks[i].exists) {return i;}}
	return -1;
}
int findFreeCoin() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!coins[i].exists) {return i;}}
	return -1;
}
int findFreeGoomba() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!goombas[i].exists) {return i;}}
	return -1;
}
int findFreeMushroom() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!mushrooms[i].exists) {return i;}}
	return -1;
}
int findFreeKoopa() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!koopas[i].exists) {return i;}}
	return -1;
}
int findFreeShell() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!shells[i].exists) {return i;}}
	return -1;
}
int findFreePiranha() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!piranhas[i].exists) {return i;}}
	return -1;
}
int findFreeParticle() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!particles[i].exists) {return i;}}
	return -1;
}
int findFreeFeather() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!feathers[i].exists) {return i;}}
	return -1;
}
int findFreeBrickBlock() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!brickBlocks[i].exists) {return i;}}
	return -1;
}
int findFreePipeEntrance() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!pipeEntrances[i].exists) {return i;}}
	return -1;
}

#endif