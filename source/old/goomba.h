#ifndef GOOMBA_H
#define GOOMBA_H

#include "global.h"
#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"
#include "objectsHolder.h"
#include "particle.h"

void initGoomba(Goomba* goomba, int x, int y, bool winged) {
	setVec2(&goomba->pos, x, y);
	setVec2(&goomba->vel, 0, 0);
	goomba->exists = 1;
	goomba->facing = 1;
	goomba->ground = 1;
	goomba->winged = winged;
	goomba->jumpTimer = 0;
	
	initAnimation(&goomba->shuffleAnim, goombaSprites, 2, 0, osGetTime(), 200);
}

void squishGoomba(Goomba* goomba) {
	goomba->exists = 0;
	
	int partIndex = findFreeParticle();
	if(partIndex != -1) {initParticle(&particles[partIndex], &goombaStompedSprite, 1, 400, goomba->pos.x - 8, goomba->pos.y - 16);}
}

void updateGoomba(Goomba* goomba, Level* level, int timeDelta) {
	int surroundingSolids = checkSurroundingSolids((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), level);
	int surroundingPlatforms = checkSurroundingPlatforms((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), level);
	if(goomba->vel.y >= 0) {surroundingSolids += surroundingPlatforms;}
	
	bool leftLedge = 1;
	bool rightLedge = 1;
	
	if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(goomba->pos.x - 6, goomba->pos.y, 1, 0.5f), getTileBB((int)(goomba->pos.x / 16) - 1, (int)((goomba->pos.y - 7) / 16) + 1))) {leftLedge = 0;}
	if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(goomba->pos.x - 6, goomba->pos.y, 1, 0.5f), getTileBB((int)(goomba->pos.x / 16),     (int)((goomba->pos.y - 7) / 16) + 1))) {leftLedge = 0;}
	if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(goomba->pos.x + 5, goomba->pos.y, 1, 0.5f), getTileBB((int)(goomba->pos.x / 16),     (int)((goomba->pos.y - 7) / 16) + 1))) {rightLedge = 0;}
	if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(goomba->pos.x + 5, goomba->pos.y, 1, 0.5f), getTileBB((int)(goomba->pos.x / 16) + 1, (int)((goomba->pos.y - 7) / 16) + 1))) {rightLedge = 0;}
	
	goomba->ground = false;
	if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(goomba->pos.x - 5, goomba->pos.y - 14, 10, 14.5f), getTileBB((int)(goomba->pos.x / 16) - 1, (int)((goomba->pos.y - 7) / 16) + 1))) {goomba->ground = true;}
	if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(goomba->pos.x - 5, goomba->pos.y - 14, 10, 14.5f), getTileBB((int)(goomba->pos.x / 16),     (int)((goomba->pos.y - 7) / 16) + 1))) {goomba->ground = true;}
	if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(goomba->pos.x - 5, goomba->pos.y - 14, 10, 14.5f), getTileBB((int)(goomba->pos.x / 16) + 1, (int)((goomba->pos.y - 7) / 16) + 1))) {goomba->ground = true;}
	
	if(leftLedge && rightLedge) {
		leftLedge = 0;
		rightLedge = 0;
	}

	if(goomba->facing == 1 && rightLedge) {goomba->facing = -1;}
	else if(goomba->facing == -1 && leftLedge) {goomba->facing = 1;}
	
	goomba->vel.x = 0.02f * goomba->facing;
	
	if(!goomba->ground) {goomba->vel.y += 0.005f;}
	else if(goomba->jumpTimer == 0 && goomba->winged) {
		goomba->jumpTimer = 1000;
		goomba->vel.y = -0.15f;
	}

	goomba->pos.x += goomba->vel.x * timeDelta;
	goomba->pos.y += goomba->vel.y * timeDelta;
	
	surroundingSolids = checkSurroundingSolids((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), level);
	surroundingPlatforms = checkSurroundingPlatforms((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), level);
	int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
	int xTests[numTestSolids];
	int yTests[numTestSolids];
	getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, goomba->pos.x, goomba->pos.y - 7);
	
	for(int i = 0; i < numTestSolids; i++) {
		if(checkBBOverlap(getBB(goomba->pos.x - 6, goomba->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]))) {
			Vec2 overlap = findSmallestOverlap(getBB(goomba->pos.x - 6, goomba->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]), surroundingSolids, goomba->vel, checkPlatform(getMapValue(level, xTests[i], yTests[i])));
			
			goomba->pos.x -= overlap.x;
			goomba->pos.y -= overlap.y;
			
			if(overlap.x != 0) {
				goomba->vel.x = 0;
				goomba->facing *= -1;
			}
			if(overlap.y != 0) {goomba->vel.y = 0;}
			
			if(overlap.x != 0 && overlap.y != 0) {break;}
		}
	}

	if(goomba->ground && goomba->jumpTimer > 0) {goomba->jumpTimer -= timeDelta;}
	if(goomba->jumpTimer < 0) {goomba->jumpTimer = 0;}
}
void drawGoomba(Goomba* goomba, Vec2 camPos) {
	drawSprite(&goomba->shuffleAnim.sprites[getAnimFrame(goomba->shuffleAnim)], (int)goomba->pos.x - (int)camPos.x - 8, (int)goomba->pos.y - (int)camPos.y - 16);
	if(goomba->winged) {drawSprite(&goombaWingsSprites[getAnimFrame(goomba->shuffleAnim)], (int)goomba->pos.x - (int)camPos.x - 10, (int)goomba->pos.y - (int)camPos.y - 24);}
}

#endif