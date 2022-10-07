#ifndef KOOPA_H
#define KOOPA_H

#include "csimple.h"
#include "collision.h"

typedef struct {
	Vec2 pos;
	Animation anim;
	bool exists;
	int facing;
	bool shouldSpawnShell;
} Koopa;

void initKoopa(Koopa* koopa, int x, int y) {
	koopa->pos.x = x;
	koopa->pos.y = y;
	koopa->exists = 1;
	koopa->facing = -1;
	koopa->shouldSpawnShell = 0;
	
	koopa->anim.sprites = koopaRedSprites;
	koopa->anim.size = 2;
	koopa->anim.frame = 0;
	koopa->anim.frameStartTime = osGetTime();
	koopa->anim.frameLength = 100;
}
void updateKoopa(Koopa* koopa, int timeDelta) {
	if(osGetTime() - koopa->anim.frameStartTime > koopa->anim.frameLength) {
		koopa->anim.frameStartTime = osGetTime();
		koopa->anim.frame++;
		if(koopa->anim.frame >= koopa->anim.size) {koopa->anim.frame = 0;}
	}
}
void drawKoopa(Koopa* koopa, Vec2 camPos) {drawSpriteScale(&koopa->anim.sprites[koopa->anim.frame], koopa->pos.x - (int)camPos.x - 8, koopa->pos.y - (int)camPos.y - 27, -koopa->facing, 1);}

BoundBox getKoopaBB(Koopa* koopa) {
	BoundBox output;
	output.x = koopa->pos.x - 6;
	output.y = koopa->pos.y - 25;
	output.w = 12;
	output.h = 25;
	
	return output;
}

#endif