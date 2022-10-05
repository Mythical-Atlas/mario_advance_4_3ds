#ifndef GOOMBA_H
#define GOOMBA_H

#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"

typedef struct {
	Vec2 pos;
	Animation shuffleAnim;
	bool exists;
} Goomba;

void initGoomba(Goomba* goomba, int x, int y) {
	goomba->pos.x = x;
	goomba->pos.y = y;
	goomba->exists = 1;
	
	goomba->shuffleAnim.sprites = goombaSprites;
	goomba->shuffleAnim.size = 2;
	goomba->shuffleAnim.frame = 0;
	goomba->shuffleAnim.frameStartTime = osGetTime();
	goomba->shuffleAnim.frameLength = 200;
}
void updateGoomba(Goomba* goomba, int timeDelta) {
	if(osGetTime() - goomba->shuffleAnim.frameStartTime > goomba->shuffleAnim.frameLength) {
		goomba->shuffleAnim.frameStartTime = osGetTime();
		goomba->shuffleAnim.frame++;
		if(goomba->shuffleAnim.frame >= goomba->shuffleAnim.size) {goomba->shuffleAnim.frame = 0;}
	}
}
void drawGoomba(Goomba* goomba, Vec2 camPos) {drawSprite(&goomba->shuffleAnim.sprites[goomba->shuffleAnim.frame], goomba->pos.x - (int)camPos.x - 8, goomba->pos.y - (int)camPos.y - 16);}

BoundBox getGoombaBB(Goomba* goomba) {
	BoundBox output;
	output.x = goomba->pos.x - 6;
	output.y = goomba->pos.y - 14;
	output.w = 12;
	output.h = 14;
	
	return output;
}

#endif