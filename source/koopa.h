#ifndef KOOPA_H
#define KOOPA_H

#include "global.h"
#include "csimple.h"
#include "collision.h"
#include "objectsHolder.h"
#include "shell.h"

void initKoopa(Koopa* koopa, int x, int y) {
	setVec2(&koopa->pos, x, y);
	setVec2(&koopa->vel, 0, 0);
	koopa->pos.x = x;
	koopa->pos.y = y;
	koopa->exists = 1;
	koopa->ground = 1;
	koopa->facing = -1;
	koopa->shouldSpawnShell = 0;
	
	koopa->anim.sprites = koopaRedSprites;
	koopa->anim.size = 2;
	koopa->anim.frame = 0;
	koopa->anim.frameStartTime = osGetTime();
	koopa->anim.frameLength = 100;
}

void spawnShell(Koopa* koopa) {
	koopa->exists = 0;
	int shellIndex = findFreeShell();
	if(shellIndex != -1) {initShell(&shells[shellIndex], koopa->pos.x, koopa->pos.y);}
}

void updateKoopa(Koopa* koopa, Tilemap tilemap, int timeDelta) {
	int surroundingSolids = checkSurroundingSolids((int)(koopa->pos.x / 16), (int)((koopa->pos.y - 7) / 16), tilemap, 200, 15);
	int surroundingPlatforms = checkSurroundingPlatforms((int)(koopa->pos.x / 16), (int)((koopa->pos.y - 7) / 16), tilemap, 200, 15);
	if(koopa->vel.y >= 0) {surroundingSolids += surroundingPlatforms;}
	
	bool leftLedge = 1;
	bool rightLedge = 1;
	
	if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(koopa->pos.x - 6, koopa->pos.y, 1, 0.5f), getTileBB((int)(koopa->pos.x / 16) - 1, (int)((koopa->pos.y - 7) / 16) + 1))) {leftLedge = 0;}
	if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(koopa->pos.x - 6, koopa->pos.y, 1, 0.5f), getTileBB((int)(koopa->pos.x / 16),     (int)((koopa->pos.y - 7) / 16) + 1))) {leftLedge = 0;}
	if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(koopa->pos.x + 5, koopa->pos.y, 1, 0.5f), getTileBB((int)(koopa->pos.x / 16),     (int)((koopa->pos.y - 7) / 16) + 1))) {rightLedge = 0;}
	if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(koopa->pos.x + 5, koopa->pos.y, 1, 0.5f), getTileBB((int)(koopa->pos.x / 16) + 1, (int)((koopa->pos.y - 7) / 16) + 1))) {rightLedge = 0;}
	
	koopa->ground = false;
	if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(koopa->pos.x - 5, koopa->pos.y - 14, 10, 14.5f), getTileBB((int)(koopa->pos.x / 16) - 1, (int)((koopa->pos.y - 7) / 16) + 1))) {koopa->ground = true;}
	if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(koopa->pos.x - 5, koopa->pos.y - 14, 10, 14.5f), getTileBB((int)(koopa->pos.x / 16),     (int)((koopa->pos.y - 7) / 16) + 1))) {koopa->ground = true;}
	if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(koopa->pos.x - 5, koopa->pos.y - 14, 10, 14.5f), getTileBB((int)(koopa->pos.x / 16) + 1, (int)((koopa->pos.y - 7) / 16) + 1))) {koopa->ground = true;}
	
	if(koopa->facing == 1 && rightLedge) {koopa->facing = -1;}
	else if(koopa->facing == -1 && leftLedge) {koopa->facing = 1;}
	
	koopa->vel.x = 0.02f * koopa->facing;
	
	koopa->pos.x += koopa->vel.x * timeDelta;
	
	surroundingSolids = checkSurroundingSolids((int)(koopa->pos.x / 16), (int)((koopa->pos.y - 7) / 16), tilemap, 200, 15);
	surroundingPlatforms = checkSurroundingPlatforms((int)(koopa->pos.x / 16), (int)((koopa->pos.y - 7) / 16), tilemap, 200, 15);
	int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
	int xTests[numTestSolids];
	int yTests[numTestSolids];
	getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, koopa->pos.x, koopa->pos.y - 7);
	
	for(int i = 0; i < numTestSolids; i++) {
		if(checkBBOverlap(getBB(koopa->pos.x - 6, koopa->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]))) {
			Vec2 overlap = findSmallestOverlap(getBB(koopa->pos.x - 6, koopa->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]), surroundingSolids, koopa->vel, checkPlatform(getMapValue(tilemap, xTests[i], yTests[i])));
			
			koopa->pos.x -= overlap.x;
			koopa->pos.y -= overlap.y;
			
			if(overlap.x != 0) {
				koopa->vel.x = 0;
				koopa->facing *= -1;
			}
			if(overlap.y != 0) {koopa->vel.y = 0;}
			
			if(overlap.x != 0 && overlap.y != 0) {break;}
		}
	}
}
void drawKoopa(Koopa* koopa, Vec2 camPos) {
	if(osGetTime() - koopa->anim.frameStartTime > koopa->anim.frameLength) {
		koopa->anim.frameStartTime = osGetTime();
		koopa->anim.frame++;
		if(koopa->anim.frame >= koopa->anim.size) {koopa->anim.frame = 0;}
	}

	drawSpriteScale(&koopa->anim.sprites[koopa->anim.frame], (int)koopa->pos.x - (int)camPos.x - 8, (int)koopa->pos.y - (int)camPos.y - 27, -koopa->facing, 1);
}

BoundBox getKoopaBB(Koopa* koopa) {
	BoundBox output;
	output.x = koopa->pos.x - 6;
	output.y = koopa->pos.y - 25;
	output.w = 12;
	output.h = 25;
	
	return output;
}

#endif