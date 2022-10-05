#ifndef OBJECTS_HANDLER_H
#define OBJECTS_HANDLER_H

#include "csimple.h"
#include "goomba.h"
#include "mushroom.h"
#include "questionBlock.h"
#include "koopa.h"
#include "shell.h"
#include "piranha.h"
#include "particle.h"
#include "graphicsHandler.h"

#define MAX_OBJECTS 40

QuestionBlock questionBlocks[MAX_OBJECTS];
//Coin coins[MAX_OBJECTS];
Goomba goombas[MAX_OBJECTS];
Mushroom mushrooms[MAX_OBJECTS];
Koopa koopas[MAX_OBJECTS];
Shell shells[MAX_OBJECTS];
Piranha piranhas[MAX_OBJECTS];
Particle particles[MAX_OBJECTS];

int findFreeQuestionBlock() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!questionBlocks[i].exists) {return i;}}
	return -1;
}
/*int findFreeCoin() {
	for(int i = 0; i < MAX_OBJECTS; i++) {if(!coins[i].exists) {return i;}}
	return -1;
}*/
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

void initObjects() {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		questionBlocks[i].exists = 0;
		//coins[i].exists = 0;
		goombas[i].exists = 0;
		mushrooms[i].exists = 0;
		koopas[i].exists = 0;
		shells[i].exists = 0;
		piranhas[i].exists = 0;
		particles[i].exists = 0;
	}
}

void updateObjects(int timeDelta) {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		if(questionBlocks[i].exists) {
			updateQuestionBlock(&questionBlocks[i], timeDelta);
			if(questionBlocks[i].shouldSpawnItem) {
				questionBlocks[i].shouldSpawnItem = 0;
				if(questionBlocks[i].contains == BLOCK_CONTAINS_COIN) {
					int partIndex = findFreeParticle();
					if(partIndex != -1) {initParticle(&particles[partIndex], coinBumpSprites, 19, 20, questionBlocks[i].xTile * 16, questionBlocks[i].yTile * 16 - 48);}
				}
				if(questionBlocks[i].contains == BLOCK_CONTAINS_MUSHROOM) {
					int mushIndex = findFreeMushroom();
					if(mushIndex != -1) {initMushroom(&mushrooms[mushIndex], questionBlocks[i].xTile * 16 + 8, questionBlocks[i].yTile * 16 + 16);}
				}
				questionBlocks[i].contains = BLOCK_CONTAINS_NOTHING;
			}
		}
		//if(coins[i].exists) {updateCoin(&coins[i], timeDelta);}
		if(goombas[i].exists) {updateGoomba(&goombas[i], timeDelta);}
		if(mushrooms[i].exists) {updateMushroom(&mushrooms[i], timeDelta);}
		/*if(koopas[i].exists) {updateKoopa(&koopas[i], timeDelta);}
		if(shells[i].exists) {updateShell(&shells[i], timeDelta);}*/
		if(piranhas[i].exists) {updatePiranha(&piranhas[i], timeDelta);}
		if(particles[i].exists) {updateParticle(&particles[i], timeDelta);}
	}
}

void drawObjects(Vec2 camPos) {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		if(questionBlocks[i].exists) {drawQuestionBlock(&questionBlocks[i], camPos);}
		//if(coins[i].exists) {drawCoin(&coins[i], camPos);}
		if(goombas[i].exists) {drawGoomba(&goombas[i], camPos);}
		if(mushrooms[i].exists) {drawMushroom(&mushrooms[i], camPos);}
		/*if(koopas[i].exists) {drawKoopa(&koopas[i], camPos);}
		if(shells[i].exists) {drawShell(&shells[i], camPos);}*/
		if(piranhas[i].exists) {drawPiranha(&piranhas[i], camPos);}
		if(particles[i].exists) {drawParticle(&particles[i], camPos);}
	}
}

#endif