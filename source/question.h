#ifndef QUESTION_H
#define QUESTION_H

typedef struct {
	Vec2 pos;
	
	int xTile;
	int yTile;
	
	Animation questionBumpAnim;
} QuestionBlock;

void initQuestionBlock(QuestionBlock* questionBlock, int xTile, int yTile, C2D_Sprite* sprites) {
	questionBlock->xTile = xTile;
	questionBlock->yTile = yTile;
	
	questionBlock->questionBumpAnim.sprites = sprites;
	questionBlock->questionBumpAnim.size = 4;
	questionBlock->questionBumpAnim.frame = 0;
	questionBlock->questionBumpAnim.frameStartTime = osGetTime();
	questionBlock->questionBumpAnim.frameLength = 50;
}
bool updateQuestionBlock(QuestionBlock* questionBlock, int timeDelta) {
	if(osGetTime() - questionBlock->questionBumpAnim.frameStartTime > questionBlock->questionBumpAnim.frameLength) {
		questionBlock->questionBumpAnim.frame++;
		if(questionBlock->questionBumpAnim.frame >= questionBlock->questionBumpAnim.size) {
			questionBlock->questionBumpAnim.frame = questionBlock->questionBumpAnim.size - 1;
			return true;
		}
	}
	
	return false;
}

#endif