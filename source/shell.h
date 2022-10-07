#ifndef SHELL_H
#define SHELL_H

#include "csimple.h"
#include "collision.h"

typedef struct {
	Vec2 pos;
	Animation anim;
	bool exists;
	int moving;
} Shell;

void setMovement(Shell* shell, int moving) {
	shell->anim.frameStartTime = osGetTime();
	shell->anim.frame = 0;
	shell->moving = moving;
}

void initShell(Shell* shell, int x, int y) {
	shell->pos.x = x;
	shell->pos.y = y;
	shell->exists = 1;
	shell->moving = 0;
	
	shell->anim.sprites = shellRedSprites;
	shell->anim.size = 4;
	shell->anim.frame = 0;
	shell->anim.frameStartTime = osGetTime();
	shell->anim.frameLength = 100;
}
void updateShell(Shell* shell, int timeDelta) {
	if(osGetTime() - shell->anim.frameStartTime > shell->anim.frameLength) {
		shell->anim.frameStartTime = osGetTime();
		shell->anim.frame++;
		if(shell->anim.frame >= shell->anim.size) {shell->anim.frame = 0;}
	}
}
void drawShell(Shell* shell, Vec2 camPos) {
	if(shell->moving != 0) {drawSprite(&shell->anim.sprites[shell->anim.frame], shell->pos.x - (int)camPos.x - 8, shell->pos.y - (int)camPos.y - 16);}
	else {drawSprite(&shellRedSprites[0], shell->pos.x - (int)camPos.x - 8, shell->pos.y - (int)camPos.y - 16);}
}

BoundBox getShellBB(Shell* shell) {
	BoundBox output;
	output.x = shell->pos.x - 6;
	output.y = shell->pos.y - 14;
	output.w = 12;
	output.h = 14;
	
	return output;
}

#endif