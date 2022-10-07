#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"

typedef struct {
	Vec2 pos;
	Vec2 vel;
	bool exists;
	int appearing;
	int facing;
	bool ground;
} Mushroom;

void initMushroom(Mushroom* mushroom, int x, int y) {
	setVec2(&mushroom->pos, x, y);
	setVec2(&mushroom->vel, 0, 0);
	mushroom->exists = 1;
	mushroom->facing = 1;
	mushroom->ground = 1;
	mushroom->appearing = 16;
}
void updateMushroom(Mushroom* mushroom, Tilemap tilemap, int timeDelta) {
	if(mushroom->appearing > 0) {
		mushroom->pos.y--;
		mushroom->appearing--;
	}
	else {
		int surroundingSolids = checkSurroundingSolids((int)(mushroom->pos.x / 16), (int)((mushroom->pos.y - 8) / 16), tilemap, 200, 15);
		int surroundingPlatforms = checkSurroundingPlatforms((int)(mushroom->pos.x / 16), (int)((mushroom->pos.y - 8) / 16), tilemap, 200, 15);
		if(mushroom->vel.y >= 0) {surroundingSolids += surroundingPlatforms;}
		
		mushroom->ground = false;
		if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(mushroom->pos.x - 6, mushroom->pos.y, 12, 0.5f), getTileBB((int)(mushroom->pos.x / 16) - 1, (int)((mushroom->pos.y - 8) / 16) + 1))) {mushroom->ground = true;}
		if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(mushroom->pos.x - 6, mushroom->pos.y, 12, 0.5f), getTileBB((int)(mushroom->pos.x / 16),     (int)((mushroom->pos.y - 8) / 16) + 1))) {mushroom->ground = true;}
		if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(mushroom->pos.x - 6, mushroom->pos.y, 12, 0.5f), getTileBB((int)(mushroom->pos.x / 16) + 1, (int)((mushroom->pos.y - 8) / 16) + 1))) {mushroom->ground = true;}
		
		if(mushroom->ground) {mushroom->vel.x = 0.04f * mushroom->facing;}
		else {mushroom->vel.y += 0.015f;}
		
		mushroom->pos.x += mushroom->vel.x * timeDelta;
		mushroom->pos.y += mushroom->vel.y * timeDelta;
		
		surroundingSolids = checkSurroundingSolids((int)(mushroom->pos.x / 16), (int)((mushroom->pos.y - 8) / 16), tilemap, 200, 15);
		surroundingPlatforms = checkSurroundingPlatforms((int)(mushroom->pos.x / 16), (int)((mushroom->pos.y - 8) / 16), tilemap, 200, 15);
		int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
		int xTests[numTestSolids];
		int yTests[numTestSolids];
		getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, mushroom->pos.x, mushroom->pos.y - 8);
		
		for(int i = 0; i < numTestSolids; i++) {
			if(checkBBOverlap(getBB(mushroom->pos.x - 8, mushroom->pos.y - 16, 16, 16), getTileBB(xTests[i], yTests[i]))) {
				Vec2 overlap = findSmallestOverlap(getBB(mushroom->pos.x - 8, mushroom->pos.y - 16, 16, 16), getTileBB(xTests[i], yTests[i]), surroundingSolids, mushroom->vel, checkPlatform(getMapValue(tilemap, xTests[i], yTests[i])));
				
				mushroom->pos.x -= overlap.x;
				mushroom->pos.y -= overlap.y;
				
				if(overlap.x != 0) {
					mushroom->vel.x = 0;
					mushroom->facing *= -1;
				}
				if(overlap.y != 0) {mushroom->vel.y = 0;}
				
				if(overlap.x != 0 && overlap.y != 0) {break;}
			}
		}
	}
}
void drawMushroom(Mushroom* mushroom, Vec2 camPos) {drawSprite(&mushroomSprite, mushroom->pos.x - (int)camPos.x - 8, mushroom->pos.y - (int)camPos.y - 16);}

BoundBox getMushroomBB(Mushroom* mushroom) {
	BoundBox output;
	output.x = mushroom->pos.x - 8;
	output.y = mushroom->pos.y - 16;
	output.w = 16;
	output.h = 16;
	
	return output;
}

#endif