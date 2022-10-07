#ifndef GOOMBA_H
#define GOOMBA_H

#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"

typedef struct {
	Vec2 pos;
	Vec2 vel;
	Animation shuffleAnim;
	bool exists;
	int facing;
	bool ground;
	bool shouldSpawnSquish;
} Goomba;

void initGoomba(Goomba* goomba, int x, int y) {
	setVec2(&goomba->pos, x, y);
	setVec2(&goomba->vel, 0, 0);
	goomba->exists = 1;
	goomba->facing = 1;
	goomba->ground = 1;
	goomba->shouldSpawnSquish = 0;
	
	goomba->shuffleAnim.sprites = goombaSprites;
	goomba->shuffleAnim.size = 2;
	goomba->shuffleAnim.frame = 0;
	goomba->shuffleAnim.frameStartTime = osGetTime();
	goomba->shuffleAnim.frameLength = 200;
}
void updateGoomba(Goomba* goomba, Tilemap tilemap, int timeDelta) {
	int surroundingSolids = checkSurroundingSolids((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), tilemap, 200, 15);
	int surroundingPlatforms = checkSurroundingPlatforms((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), tilemap, 200, 15);
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
	
	if(goomba->facing == 1 && rightLedge) {goomba->facing = -1;}
	else if(goomba->facing == -1 && leftLedge) {goomba->facing = 1;}
	
	goomba->vel.x = 0.02f * goomba->facing;
	
	goomba->pos.x += goomba->vel.x * timeDelta;
	
	surroundingSolids = checkSurroundingSolids((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), tilemap, 200, 15);
	surroundingPlatforms = checkSurroundingPlatforms((int)(goomba->pos.x / 16), (int)((goomba->pos.y - 7) / 16), tilemap, 200, 15);
	int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
	int xTests[numTestSolids];
	int yTests[numTestSolids];
	getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, goomba->pos.x, goomba->pos.y - 7);
	
	for(int i = 0; i < numTestSolids; i++) {
		if(checkBBOverlap(getBB(goomba->pos.x - 6, goomba->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]))) {
			Vec2 overlap = findSmallestOverlap(getBB(goomba->pos.x - 6, goomba->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]), surroundingSolids, goomba->vel, checkPlatform(getMapValue(tilemap, xTests[i], yTests[i])));
			
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
}
void drawGoomba(Goomba* goomba, Vec2 camPos) {
	if(osGetTime() - goomba->shuffleAnim.frameStartTime > goomba->shuffleAnim.frameLength) {
		goomba->shuffleAnim.frameStartTime = osGetTime();
		goomba->shuffleAnim.frame++;
		if(goomba->shuffleAnim.frame >= goomba->shuffleAnim.size) {goomba->shuffleAnim.frame = 0;}
	}
	
	drawSprite(&goomba->shuffleAnim.sprites[goomba->shuffleAnim.frame], (int)goomba->pos.x - (int)camPos.x - 8, (int)goomba->pos.y - (int)camPos.y - 16);
}

BoundBox getGoombaBB(Goomba* goomba) {
	BoundBox output;
	output.x = goomba->pos.x - 6;
	output.y = goomba->pos.y - 14;
	output.w = 12;
	output.h = 14;
	
	return output;
}

#endif