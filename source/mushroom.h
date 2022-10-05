#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"

typedef struct {
	Vec2 pos;
	bool exists;
	int appearing;
} Mushroom;

void initMushroom(Mushroom* mushroom, int x, int y) {
	mushroom->pos.x = x;
	mushroom->pos.y = y;
	mushroom->exists = 1;
	mushroom->appearing = 16;
}
void updateMushroom(Mushroom* mushroom, int timeDelta) {
	if(mushroom->appearing > 0) {
		mushroom->pos.y--;
		mushroom->appearing--;
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