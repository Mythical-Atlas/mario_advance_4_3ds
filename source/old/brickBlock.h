#ifndef BRICK_BLOCK_H
#define BRICK_BLOCK_H

#include "global.h"
#include "csimple.h"
#include "graphicsHandler.h"
#include "objectsHolder.h"
#include "particle.h"

void initBrickBlock(BrickBlock* brickBlock, int xTile, int yTile) {
	brickBlock->xTile = xTile;
	brickBlock->yTile = yTile;
	brickBlock->exists = 1;

	initAnimation(&brickBlock->anim, brickBlockSprites, 4, 0, osGetTime(), 70);
}

void destroyBrickBlock(BrickBlock* brickBlock) {
	brickBlock->exists = 0;
	// spawn particles
}

void drawBrickBlock(BrickBlock* brickBlock, Vec2 camPos) {
	if(osGetTime() - brickBlock->anim.frameStartTime > brickBlock->anim.frameLength) {
		brickBlock->anim.frameStartTime = osGetTime();
		brickBlock->anim.frame++;
		if(brickBlock->anim.frame >= brickBlock->anim.size) {brickBlock->anim.frame = 0;}
	}

	drawSprite(&brickBlock->anim.sprites[brickBlock->anim.frame], brickBlock->xTile * 16 - (int)camPos.x, brickBlock->yTile * 16 - (int)camPos.y);
}

#endif