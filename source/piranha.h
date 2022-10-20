#ifndef PIRANHA_H
#define PIRANHA_H

#include "global.h"
#include "csimple.h"
#include "collision.h"

void initPiranha(Piranha* piranha, int x, int y) {
	piranha->pos.x = x;
	piranha->pos.y = y;
	piranha->exists = 1;
	piranha->riseTimer = 0;
	piranha->yOffset = 0;
	
	initAnimation(&piranha->anim, piranhaRedGreenSprites, 2, 0, osGetTime(), 100);
}
void updatePiranha(Piranha* piranha, int timeDelta) {
	if(osGetTime() - piranha->anim.frameStartTime > piranha->anim.frameLength) {
		piranha->anim.frameStartTime = osGetTime();
		piranha->anim.frame++;
		if(piranha->anim.frame >= piranha->anim.size) {piranha->anim.frame = 0;}
	}
	
	piranha->riseTimer += timeDelta;
	if(piranha->riseTimer > 4000) {piranha->riseTimer -= 4000;}
	
	if(piranha->riseTimer >= 2000) {
		if(piranha->yOffset < 0) {
			piranha->pos.y++;
			piranha->yOffset++;
		}
	}
	else if(piranha->riseTimer >= 0) {
		if(piranha->yOffset > -32) {
			piranha->pos.y--;
			piranha->yOffset--;
		}
	}
}
void drawPiranha(Piranha* piranha, Vec2 camPos) {drawSprite(&piranha->anim.sprites[piranha->anim.frame], piranha->pos.x - (int)camPos.x - 8, piranha->pos.y - (int)camPos.y - 32);}

#endif