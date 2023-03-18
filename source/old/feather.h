#ifndef FEATHER_H
#define FEATHER_H

#include "global.h"
#include "csimple.h"
#include "collision.h"
#include "graphicsHandler.h"

void initFeather(Feather* feather, int x, int y) {
	setVec2(&feather->pos, x, y);
	setVec2(&feather->vel, 0, -0.05f);
	feather->exists = 1;
	feather->facing = 1;
	feather->ground = 1;
	feather->appearing = 16;
	feather->floatTimer = 0;
}
void updateFeather(Feather* feather, Level* level, int timeDelta) {
	if(feather->appearing > 0) {
		feather->pos.y--;
		feather->appearing--;
	}
	else {
		feather->vel.x = cosf(feather->floatTimer / 300.0f) / 20.0f;
		feather->vel.y += 0.0005f + sinf(feather->floatTimer / 300.0f) / 1000.0f;
		
		feather->pos.x += feather->vel.x * timeDelta;
		feather->pos.y += feather->vel.y * timeDelta;

		if(feather->pos.y - 16 > level->maph * 16) {feather->exists = 0;}

		feather->floatTimer += timeDelta;
	}
}
void drawFeather(Feather* feather, Vec2 camPos) {drawSprite(&featherSprite, (int)feather->pos.x - (int)camPos.x - 8, (int)feather->pos.y - (int)camPos.y - 16);}

BoundBox getFeatherBB(Feather* feather) {
	BoundBox output;
	output.x = feather->pos.x - 8;
	output.y = feather->pos.y - 16;
	output.w = 16;
	output.h = 16;
	
	return output;
}

#endif