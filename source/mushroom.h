#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"

typedef struct {
	Vec2 pos;
	C2D_Sprite* sprite;
	bool exists;
} Mushroom;

void initMushroom(Mushroom* mushroom, int x, int y) {
	mushroom->pos.x = x;
	mushroom->pos.y = y;
	mushroom->exists = 1;
	
	mushroom->sprite = &mushroomSprites[0];
}
void updateMushroom(Mushroom* mushroom, int timeDelta) {}
void drawMushroom(Mushroom* mushroom, Vec2 camPos) {drawSprite(mushroom->sprite, mushroom->pos.x - (int)camPos.x - 8, mushroom->pos.y - (int)camPos.y - 16);}

BoundBox getMushroomBB(Mushroom* mushroom) {
	BoundBox output;
	output.x = mushroom->pos.x - 8;
	output.y = mushroom->pos.y - 16;
	output.w = 16;
	output.h = 16;
	
	return output;
}

#endif