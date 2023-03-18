#ifndef QUESTION_BLOCK_H
#define QUESTION_BLOCK_H

#include "global.h"
#include "csimple.h"
#include "graphicsHandler.h"
#include "objectsHolder.h"
#include "particle.h"
#include "feather.h"

#define BLOCK_CONTAINS_NOTHING  0
#define BLOCK_CONTAINS_COIN     1
#define BLOCK_CONTAINS_MUSHROOM 2
#define BLOCK_CONTAINS_FEATHER  3
#define BLOCK_CONTAINS_1UP      4

#define BLOCK_FACADE_DEAD     0
#define BLOCK_FACADE_QUESTION 1
#define BLOCK_FACADE_BRICK    2

void initQuestionBlock(QuestionBlock* questionBlock, int xTile, int yTile, int contains, int facade) {
	questionBlock->xTile = xTile;
	questionBlock->yTile = yTile;
	questionBlock->exists = 1;
	questionBlock->contains = contains;
	questionBlock->facade = facade;
	
	initAnimation(&questionBlock->anim, questionBlockSprites, 4, 0, osGetTime(), 70);
	initAnimation(&questionBlock->bumpAnim, questionBlockBumpSprites, 4, 0, osGetTime(), 20);
}

void startQuestionBlockBump(QuestionBlock* questionBlock) {
	if(questionBlock->facade != BLOCK_FACADE_DEAD) {
		questionBlock->bumpAnim.frameStartTime = osGetTime();
		questionBlock->bumping = true;
	}
}

void updateQuestionBlock(QuestionBlock* questionBlock, int timeDelta) {
	if(osGetTime() - questionBlock->anim.frameStartTime > questionBlock->anim.frameLength) {
		questionBlock->anim.frameStartTime = osGetTime();
		questionBlock->anim.frame++;
		if(questionBlock->anim.frame >= questionBlock->anim.size) {questionBlock->anim.frame = 0;}
	}
	
	if(questionBlock->bumping) {
		if(osGetTime() - questionBlock->bumpAnim.frameStartTime > questionBlock->bumpAnim.frameLength) {
			questionBlock->bumpAnim.frameStartTime = osGetTime();
			questionBlock->bumpAnim.frame++;
			if(questionBlock->bumpAnim.frame >= questionBlock->bumpAnim.size) {
				questionBlock->bumpAnim.frame = 0;
				questionBlock->bumping = false;

				if(questionBlock->contains == BLOCK_CONTAINS_COIN) {
					int partIndex = findFreeParticle();
					if(partIndex != -1) {initParticle(&particles[partIndex], coinBumpSprites, 19, 20, questionBlock->xTile * 16, questionBlock->yTile * 16 - 48);}
				}
				if(questionBlock->contains == BLOCK_CONTAINS_MUSHROOM) {
					int mushIndex = findFreeMushroom();
					if(mushIndex != -1) {initMushroom(&mushrooms[mushIndex], questionBlock->xTile * 16 + 8, questionBlock->yTile * 16 + 16);}
				}
				if(questionBlock->contains == BLOCK_CONTAINS_FEATHER) {
					int feathIndex = findFreeFeather();
					if(feathIndex != -1) {initFeather(&feathers[feathIndex], questionBlock->xTile * 16 + 8, questionBlock->yTile * 16 + 16);}
				}
				if(questionBlock->contains == BLOCK_CONTAINS_1UP) {
					int mushIndex = findFreeMushroom();
					if(mushIndex != -1) {initLifeShroom(&mushrooms[mushIndex], questionBlock->xTile * 16 + 8, questionBlock->yTile * 16 + 16);}
				}

				questionBlock->contains = BLOCK_CONTAINS_NOTHING;
				questionBlock->facade = BLOCK_FACADE_DEAD;
			}
		}
	}
}

void drawQuestionBlock(QuestionBlock* questionBlock, Vec2 camPos) {
	if(!questionBlock->bumping) {
		if(questionBlock->facade == BLOCK_FACADE_DEAD) {drawSprite(&tileSprites[154], questionBlock->xTile * 16 - (int)camPos.x, questionBlock->yTile * 16 - (int)camPos.y);}
		if(questionBlock->facade == BLOCK_FACADE_QUESTION) {drawSprite(&questionBlock->anim.sprites[questionBlock->anim.frame], questionBlock->xTile * 16 - (int)camPos.x, questionBlock->yTile * 16 - (int)camPos.y);}
		if(questionBlock->facade == BLOCK_FACADE_BRICK) {drawSprite(&tileSprites[171], questionBlock->xTile * 16 - (int)camPos.x, questionBlock->yTile * 16 - (int)camPos.y);}
	}
	else {drawSprite(&questionBlock->bumpAnim.sprites[questionBlock->bumpAnim.frame], questionBlock->xTile * 16 - (int)camPos.x, questionBlock->yTile * 16 - (int)camPos.y - 5);}
}

#endif