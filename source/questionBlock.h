/*#ifndef QUESTION_BLOCK_H
#define QUESTION_BLOCK_H

#include "csimple.h"
#include "graphicsHandler.h"

typedef struct {
	Vec2 pos;
	
	int xTile;
	int yTile;
	
	Animation questionBumpAnim;
	bool exists;
} QuestionBlock;

void initQuestionBlock(QuestionBlock* questionBlock, int xTile, int yTile) {
	questionBlock->xTile = xTile;
	questionBlock->yTile = yTile;
	questionBlock->exists = 1;
	
	questionBlock->questionBumpAnim.sprites = questionBlockSprites;
	questionBlock->questionBumpAnim.size = 4;
	questionBlock->questionBumpAnim.frame = 0;
	questionBlock->questionBumpAnim.frameStartTime = osGetTime();
	questionBlock->questionBumpAnim.frameLength = 50;
}
bool updateQuestionBlock(QuestionBlock* questionBlock, int timeDelta) {
	if(osGetTime() - questionBlock->questionBumpAnim.frameStartTime > questionBlock->questionBumpAnim.frameLength) {
		questionBlock->questionBumpAnim.frameStartTime = osGetTime();
		questionBlock->questionBumpAnim.frame++;
		if(questionBlock->questionBumpAnim.frame >= questionBlock->questionBumpAnim.size) {
			questionBlock->questionBumpAnim.frame = questionBlock->questionBumpAnim.size - 1;
			return true;
		}
	}
	
	return false;
}

#endif*/