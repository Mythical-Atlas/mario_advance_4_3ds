#ifndef PIRANHA_H
#define PIRANHA_H

#include "csimple.h"
#include "collision.h"

typedef struct {
	Vec2 pos;
	C2D_Sprite* sprite;
	bool exists;
} Piranha;
/*
void initMushroom(Mushroom* mushroom, C2D_Sprite* sprite, int x, int y) {
	mushroom->pos.x = x;
	mushroom->pos.y = y;
	
	mushroom->sprite = sprite;
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
*/
#endif