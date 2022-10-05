#ifndef QUESTION_BLOCK_H
#define QUESTION_BLOCK_H

#include "csimple.h"
#include "graphicsHandler.h"
#include "objectsHandler.h"
#include "particle.h"

#define BLOCK_CONTAINS_NOTHING  0
#define BLOCK_CONTAINS_COIN     1
#define BLOCK_CONTAINS_MUSHROOM 2

#define BLOCK_FACADE_DEAD     0
#define BLOCK_FACADE_QUESTION 1
#define BLOCK_FACADE_BRICK    2

typedef struct {
	int xTile;
	int yTile;
	bool exists;
	
	int contains;
	int facade;
	bool bumping;
	bool shouldSpawnItem;
	
	Animation anim;
	Animation bumpAnim;
} QuestionBlock;

void initQuestionBlock(QuestionBlock* questionBlock, int xTile, int yTile, int contains, int facade) {
	questionBlock->xTile = xTile;
	questionBlock->yTile = yTile;
	questionBlock->exists = 1;
	questionBlock->contains = contains;
	questionBlock->facade = facade;
	questionBlock->shouldSpawnItem = false;
	
	questionBlock->anim.sprites = questionBlockSprites;
	questionBlock->anim.size = 4;
	questionBlock->anim.frame = 0;
	questionBlock->anim.frameStartTime = osGetTime();
	questionBlock->anim.frameLength = 70;
	
	questionBlock->bumpAnim.sprites = questionBlockBumpSprites;
	questionBlock->bumpAnim.size = 4;
	questionBlock->bumpAnim.frame = 0;
	questionBlock->bumpAnim.frameStartTime = osGetTime();
	questionBlock->bumpAnim.frameLength = 20;
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
				questionBlock->shouldSpawnItem = true;
				
				//questionBlock->contains = BLOCK_CONTAINS_NOTHING;
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