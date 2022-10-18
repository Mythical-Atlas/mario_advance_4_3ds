#ifndef FEATHER_H
#define FEATHER_H

#include "global.h"
#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"

void initFeather(Feather* feather, int x, int y) {
	setVec2(&feather->pos, x, y);
	setVec2(&feather->vel, 0, 0);
	feather->exists = 1;
	feather->facing = 1;
	feather->ground = 1;
	feather->appearing = 16;
}
void updateFeather(Feather* feather, Tilemap tilemap, int timeDelta) {
	if(feather->appearing > 0) {
		feather->pos.y--;
		feather->appearing--;
	}
	else {
		int surroundingSolids = checkSurroundingSolids((int)(feather->pos.x / 16), (int)((feather->pos.y - 8) / 16), tilemap, 200, 15);
		int surroundingPlatforms = checkSurroundingPlatforms((int)(feather->pos.x / 16), (int)((feather->pos.y - 8) / 16), tilemap, 200, 15);
		if(feather->vel.y >= 0) {surroundingSolids += surroundingPlatforms;}
		
		feather->ground = false;
		if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(feather->pos.x - 6, feather->pos.y, 12, 0.5f), getTileBB((int)(feather->pos.x / 16) - 1, (int)((feather->pos.y - 8) / 16) + 1))) {feather->ground = true;}
		if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(feather->pos.x - 6, feather->pos.y, 12, 0.5f), getTileBB((int)(feather->pos.x / 16),     (int)((feather->pos.y - 8) / 16) + 1))) {feather->ground = true;}
		if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(feather->pos.x - 6, feather->pos.y, 12, 0.5f), getTileBB((int)(feather->pos.x / 16) + 1, (int)((feather->pos.y - 8) / 16) + 1))) {feather->ground = true;}
		
		if(feather->ground) {feather->vel.x = 0.04f * feather->facing;}
		else {feather->vel.y += 0.015f;}
		
		feather->pos.x += feather->vel.x * timeDelta;
		feather->pos.y += feather->vel.y * timeDelta;
		
		surroundingSolids = checkSurroundingSolids((int)(feather->pos.x / 16), (int)((feather->pos.y - 8) / 16), tilemap, 200, 15);
		surroundingPlatforms = checkSurroundingPlatforms((int)(feather->pos.x / 16), (int)((feather->pos.y - 8) / 16), tilemap, 200, 15);
		int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
		int xTests[numTestSolids];
		int yTests[numTestSolids];
		getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, feather->pos.x, feather->pos.y - 8);
		
		for(int i = 0; i < numTestSolids; i++) {
			if(checkBBOverlap(getBB(feather->pos.x - 8, feather->pos.y - 16, 16, 16), getTileBB(xTests[i], yTests[i]))) {
				Vec2 overlap = findSmallestOverlap(getBB(feather->pos.x - 8, feather->pos.y - 16, 16, 16), getTileBB(xTests[i], yTests[i]), surroundingSolids, feather->vel, checkPlatform(getMapValue(tilemap, xTests[i], yTests[i])));
				
				feather->pos.x -= overlap.x;
				feather->pos.y -= overlap.y;
				
				if(overlap.x != 0) {
					feather->vel.x = 0;
					feather->facing *= -1;
				}
				if(overlap.y != 0) {feather->vel.y = 0;}
				
				if(overlap.x != 0 && overlap.y != 0) {break;}
			}
		}
	}
}
void drawFeather(Feather* feather, Vec2 camPos) {drawSprite(&featherSprite, feather->pos.x - (int)camPos.x - 8, feather->pos.y - (int)camPos.y - 16);}

BoundBox getFeatherBB(Feather* feather) {
	BoundBox output;
	output.x = feather->pos.x - 8;
	output.y = feather->pos.y - 16;
	output.w = 16;
	output.h = 16;
	
	return output;
}

#endif