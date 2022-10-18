#ifndef OBJECTS_HANDLER_H
#define OBJECTS_HANDLER_H

#include "global.h"
#include "csimple.h"
#include "goomba.h"
#include "mushroom.h"
#include "questionBlock.h"
#include "koopa.h"
#include "shell.h"
#include "piranha.h"
#include "particle.h"
#include "graphicsHandler.h"
#include "objectsHolder.h"
#include "coin.h"

void initObjects() {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		questionBlocks[i].exists = 0;
		coins[i].exists = 0;
		goombas[i].exists = 0;
		mushrooms[i].exists = 0;
		koopas[i].exists = 0;
		shells[i].exists = 0;
		piranhas[i].exists = 0;
		particles[i].exists = 0;
	}
}

void updateObjects(Tilemap tilemap, int timeDelta) {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		if(questionBlocks[i].exists) {updateQuestionBlock(&questionBlocks[i], timeDelta);}
		if(goombas[i].exists) {updateGoomba(&goombas[i], tilemap, timeDelta);}
		if(mushrooms[i].exists) {updateMushroom(&mushrooms[i], tilemap, timeDelta);}
		if(koopas[i].exists) {updateKoopa(&koopas[i], tilemap, timeDelta);}
		if(shells[i].exists) {updateShell(&shells[i], tilemap, questionBlocks, timeDelta);}
		if(piranhas[i].exists) {updatePiranha(&piranhas[i], timeDelta);}
		if(particles[i].exists) {updateParticle(&particles[i], timeDelta);}
	}
}

void drawObjects(Vec2 camPos) {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		if(questionBlocks[i].exists) {drawQuestionBlock(&questionBlocks[i], camPos);}
		if(coins[i].exists) {drawCoin(&coins[i], camPos);}
		if(goombas[i].exists) {drawGoomba(&goombas[i], camPos);}
		if(mushrooms[i].exists) {drawMushroom(&mushrooms[i], camPos);}
		if(koopas[i].exists) {drawKoopa(&koopas[i], camPos);}
		if(shells[i].exists) {drawShell(&shells[i], camPos);}
		if(piranhas[i].exists) {drawPiranha(&piranhas[i], camPos);}
		if(particles[i].exists) {drawParticle(&particles[i], camPos);}
	}
}

#endif