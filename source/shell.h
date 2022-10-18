#ifndef SHELL_H
#define SHELL_H

#include "global.h"
#include "csimple.h"
#include "collision.h"
#include "questionBlock.h"
#include "goomba.h"

#define MAX_OBJECTS 40

void setMovement(Shell* shell, int moving) {
	shell->anim.frameStartTime = osGetTime();
	shell->anim.frame = 0;
	shell->moving = moving;
}

void initShell(Shell* shell, int x, int y) {
	setVec2(&shell->pos, x, y);
	setVec2(&shell->vel, 0, 0);
	shell->exists = 1;
	shell->ground = 1;
	shell->moving = 0;
	
	shell->anim.sprites = shellRedSprites;
	shell->anim.size = 4;
	shell->anim.frame = 0;
	shell->anim.frameStartTime = osGetTime();
	shell->anim.frameLength = 100;

	if(!shell->stompSound.allocated) {openSoundFile(&shell->stompSound, "romfs:/stomp.raw", 0, 2);}
	shell->stompSound.fileEnd = 2;
	if(!shell->bumpSound.allocated) {openSoundFile(&shell->bumpSound, "romfs:/bump.raw", 0, 2);}
	shell->bumpSound.fileEnd = 2;
	if(!shell->coinSound.allocated) {openSoundFile(&shell->coinSound, "romfs:/coin.raw", 0, 3);}
	shell->coinSound.fileEnd = 2;
}

void playShellStompSound(Shell* shell) {
	ndspChnWaveBufClear(2);
	ndspChnReset(2);
	ndspChnSetInterp(2, NDSP_INTERP_LINEAR);
	ndspChnSetRate(2, SAMPLERATE);
	ndspChnSetFormat(2, NDSP_FORMAT_STEREO_PCM16);
	
	shell->stompSound.fileEnd = 0;
	playSound(&shell->stompSound);
}
void playShellBumpSound(Shell* shell) {
	ndspChnWaveBufClear(2);
	ndspChnReset(2);
	ndspChnSetInterp(2, NDSP_INTERP_LINEAR);
	ndspChnSetRate(2, SAMPLERATE);
	ndspChnSetFormat(2, NDSP_FORMAT_STEREO_PCM16);
	
	shell->bumpSound.fileEnd = 0;
	playSound(&shell->bumpSound);
}
void playShellCoinSound(Shell* shell) {
	ndspChnWaveBufClear(3);
	ndspChnReset(3);
	ndspChnSetInterp(3, NDSP_INTERP_LINEAR);
	ndspChnSetRate(3, SAMPLERATE);
	ndspChnSetFormat(3, NDSP_FORMAT_STEREO_PCM16);
	
	shell->coinSound.fileEnd = 0;
	playSound(&shell->coinSound);
}

BoundBox getShellBB(Shell* shell) {
	BoundBox output;
	output.x = shell->pos.x - 6;
	output.y = shell->pos.y - 14;
	output.w = 12;
	output.h = 14;
	
	return output;
}

void updateShell(Shell* shell, Tilemap tilemap, QuestionBlock* questionBlocks, int timeDelta) {
	int surroundingSolids = checkSurroundingSolids((int)(shell->pos.x / 16), (int)((shell->pos.y - 7) / 16), tilemap, 200, 15);
	int surroundingPlatforms = checkSurroundingPlatforms((int)(shell->pos.x / 16), (int)((shell->pos.y - 7) / 16), tilemap, 200, 15);
	if(shell->vel.y >= 0) {surroundingSolids += surroundingPlatforms;}
	
	//bool leftLedge = 1;
	//bool rightLedge = 1;
	
	//if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(shell->pos.x - 6, shell->pos.y, 1, 0.5f), getTileBB((int)(shell->pos.x / 16) - 1, (int)((shell->pos.y - 7) / 16) + 1))) {leftLedge = 0;}
	//if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(shell->pos.x - 6, shell->pos.y, 1, 0.5f), getTileBB((int)(shell->pos.x / 16),     (int)((shell->pos.y - 7) / 16) + 1))) {leftLedge = 0;}
	//if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(shell->pos.x + 5, shell->pos.y, 1, 0.5f), getTileBB((int)(shell->pos.x / 16),     (int)((shell->pos.y - 7) / 16) + 1))) {rightLedge = 0;}
	//if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(shell->pos.x + 5, shell->pos.y, 1, 0.5f), getTileBB((int)(shell->pos.x / 16) + 1, (int)((shell->pos.y - 7) / 16) + 1))) {rightLedge = 0;}
	
	shell->ground = false;
	if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(shell->pos.x - 5, shell->pos.y - 14, 10, 14.5f), getTileBB((int)(shell->pos.x / 16) - 1, (int)((shell->pos.y - 7) / 16) + 1))) {shell->ground = true;}
	if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(shell->pos.x - 5, shell->pos.y - 14, 10, 14.5f), getTileBB((int)(shell->pos.x / 16),     (int)((shell->pos.y - 7) / 16) + 1))) {shell->ground = true;}
	if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(shell->pos.x - 5, shell->pos.y - 14, 10, 14.5f), getTileBB((int)(shell->pos.x / 16) + 1, (int)((shell->pos.y - 7) / 16) + 1))) {shell->ground = true;}
	
	//if(shell->facing == 1 && rightLedge) {shell->facing = -1;}
	//else if(shell->facing == -1 && leftLedge) {shell->facing = 1;}
	
	if(shell->moving != 0) {shell->vel.x = 0.15f * shell->moving;}
	else {shell->vel.x = 0;}

	if(!shell->ground) {shell->vel.y += 0.015f;}

	shell->pos.x += shell->vel.x * timeDelta;
	shell->pos.y += shell->vel.y * timeDelta;
	
	surroundingSolids = checkSurroundingSolids((int)(shell->pos.x / 16), (int)((shell->pos.y - 7) / 16), tilemap, 200, 15);
	surroundingPlatforms = checkSurroundingPlatforms((int)(shell->pos.x / 16), (int)((shell->pos.y - 7) / 16), tilemap, 200, 15);
	int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
	int xTests[numTestSolids];
	int yTests[numTestSolids];
	getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, shell->pos.x, shell->pos.y - 7);
	
	for(int i = 0; i < numTestSolids; i++) {
		if(checkBBOverlap(getBB(shell->pos.x - 6, shell->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]))) {
			Vec2 overlap = findSmallestOverlap(getBB(shell->pos.x - 6, shell->pos.y - 14, 12, 14), getTileBB(xTests[i], yTests[i]), surroundingSolids, shell->vel, checkPlatform(getMapValue(tilemap, xTests[i], yTests[i])));
			
			shell->pos.x -= overlap.x;
			shell->pos.y -= overlap.y;
			
			if(overlap.x != 0) {
				shell->vel.x = 0;
				shell->moving *= -1;
			}
			if(overlap.y != 0) {shell->vel.y = 0;}
			
			if(overlap.y == 0 && overlap.x != 0) {
				for(int q = 0; q < MAX_OBJECTS; q++) {
					if(questionBlocks[q].xTile == xTests[i] && questionBlocks[q].yTile == yTests[i]) {
						startQuestionBlockBump(&questionBlocks[q]);
						playShellBumpSound(shell);
						if(questionBlocks[q].contains == BLOCK_CONTAINS_COIN) {playShellCoinSound(shell);}
					}
				}
			}

			if(overlap.x != 0 && overlap.y != 0) {break;}
		}
	}

	if(shell->moving != 0) {
		for(int g = 0; g < MAX_OBJECTS; g++) {
			if(goombas[g].exists) {
				if(checkBBOverlap(getShellBB(shell), getGoombaBB(&goombas[g]))) {
					squishGoomba(&goombas[g]);
					playShellStompSound(shell);
				}
			}
		}
	}
}
void drawShell(Shell* shell, Vec2 camPos) {
	if(osGetTime() - shell->anim.frameStartTime > shell->anim.frameLength) {
		shell->anim.frameStartTime = osGetTime();
		shell->anim.frame++;
		if(shell->anim.frame >= shell->anim.size) {shell->anim.frame = 0;}
	}

	if(shell->moving != 0) {drawSprite(&shell->anim.sprites[shell->anim.frame], (int)shell->pos.x - (int)camPos.x - 8, (int)shell->pos.y - (int)camPos.y - 16);}
	else {drawSprite(&shellRedSprites[0], (int)shell->pos.x - (int)camPos.x - 8, (int)shell->pos.y - (int)camPos.y - 16);}
}

#endif