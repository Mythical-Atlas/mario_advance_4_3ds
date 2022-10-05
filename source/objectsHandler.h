#ifndef OBJECTS_HANDLER_H
#define OBJECTS_HANDLER_H

#include "csimple.h"
#include "goomba.h"
#include "mushroom.h"
#include "koopa.h"
#include "shell.h"
#include "piranha.h"
#include "particle.h"
#include "graphicsHandler.h"

#define MAX_OBJECTS 40

Goomba goombas[MAX_OBJECTS];
Mushroom mushrooms[MAX_OBJECTS];
Koopa koopas[MAX_OBJECTS];
Shell shells[MAX_OBJECTS];
Piranha piranhas[MAX_OBJECTS];
Particle particles[MAX_OBJECTS];

int potentialQuestionBlocks[MAX_OBJECTS];

void initObjects() {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		goombas[i].exists = 0;
		mushrooms[i].exists = 0;
		koopas[i].exists = 0;
		shells[i].exists = 0;
		piranhas[i].exists = 0;
		particles[i].exists = 0;
		
		potentialQuestionBlocks[i] = 0;
	}
}

void updateObjects(int timeDelta) {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		if(goombas[i].exists) {updateGoomba(&goombas[i], timeDelta);}
		//if(mushrooms[i].exists) {updateMushroom(&mushrooms[i], timeDelta);}
		/*if(koopas[i].exists) {updateKoopa(&koopas[i], timeDelta);}
		if(shells[i].exists) {updateShell(&shells[i], timeDelta);}
		if(piranhas[i].exists) {updatePiranha(&piranhas[i], timeDelta);}*/
		if(particles[i].exists) {updateParticle(&particles[i], timeDelta);}
	}
}

void drawObjects(Vec2 camPos) {
	for(int i = 0; i < MAX_OBJECTS; i++) {
		if(goombas[i].exists) {drawGoomba(&goombas[i], camPos);}
		if(mushrooms[i].exists) {drawMushroom(&mushrooms[i], camPos);}
		/*if(koopas[i].exists) {drawKoopa(&koopas[i], camPos);}
		if(shells[i].exists) {drawShell(&shells[i], camPos);}
		if(piranhas[i].exists) {drawPiranha(&piranhas[i], camPos);}*/
		if(particles[i].exists) {drawParticle(&particles[i], camPos);}
	}
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

#endif