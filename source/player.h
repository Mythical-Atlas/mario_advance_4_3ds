#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>

#include "collision.h"
#include "csimple.h"
#include "goomba.h"
#include "mushroom.h"
#include "objectsHandler.h"
#include "graphicsHandler.h"
#include "questionBlock.h"
#include "particle.h"

#define WALK_ACCEL        0.003f
#define WALK_MAX_SPEED    0.08f
#define RUN_ACCEL         0.006f
#define RUN_MAX_SPEED     0.12f
#define SKID_ACCEL        0.01f
#define JUMP_IMPULSE      0.35f
#define JUMP_STOP_GRAVITY 0.05f
#define GRAVITY           0.015f
#define MAX_FALL_SPEED    0.1f

#define STATE_IDLE  0
#define STATE_WALK  1
#define STATE_SKID  2
#define STATE_JUMP  3
#define STATE_FALL  4
#define STATE_DEATH 5
#define STATE_RUN   6
#define STATE_LEAP  7

#define ANIM_IDLE  0
#define ANIM_WALK  1
#define ANIM_SKID  2
#define ANIM_JUMP  3
#define ANIM_FALL  4
#define ANIM_DEATH 5
#define ANIM_RUN   6
#define ANIM_LEAP  7

typedef struct {
	Vec2 pos;
	Vec2 vel; // measured in pixels/ms
	
	bool ground;
	int facing; // 1 = right, -1 = left
	bool health;
	
	int deathTimer;
	int pTimer;
	
	int state;
	int animation;
	
	Animation smallWalkAnim;
	Animation smallRunAnim;
	Animation bigWalkAnim;
	Animation bigRunAnim;
	
	AudioFile jumpSound;
} Player;

int getNumTests(int surroundingSolids) {
	int numTestSolids = 0;
	if((surroundingSolids &   1) ==   1) {numTestSolids++;}
	if((surroundingSolids &   2) ==   2) {numTestSolids++;}
	if((surroundingSolids &   4) ==   4) {numTestSolids++;}
	if((surroundingSolids &   8) ==   8) {numTestSolids++;}
	if((surroundingSolids &  16) ==  16) {numTestSolids++;}
	if((surroundingSolids &  32) ==  32) {numTestSolids++;}
	if((surroundingSolids &  64) ==  64) {numTestSolids++;}
	if((surroundingSolids & 128) == 128) {numTestSolids++;}
	
	return numTestSolids;
}
void getTestPositions(int surroundingSolids, int numTestSolids, int* xTests, int* yTests, Player* player) {
	int testIndex = 0;
	
	if((surroundingSolids &   1) ==   1) {xTests[testIndex] = (int)(player->pos.x / 16) - 1; yTests[testIndex++] = (int)((player->pos.y - 8) / 16) - 1;}
	if((surroundingSolids &   2) ==   2) {xTests[testIndex] = (int)(player->pos.x / 16)    ; yTests[testIndex++] = (int)((player->pos.y - 8) / 16) - 1;}
	if((surroundingSolids &   4) ==   4) {xTests[testIndex] = (int)(player->pos.x / 16) + 1; yTests[testIndex++] = (int)((player->pos.y - 8) / 16) - 1;}
	if((surroundingSolids &   8) ==   8) {xTests[testIndex] = (int)(player->pos.x / 16) - 1; yTests[testIndex++] = (int)((player->pos.y - 8) / 16)    ;}
	if((surroundingSolids &  16) ==  16) {xTests[testIndex] = (int)(player->pos.x / 16) + 1; yTests[testIndex++] = (int)((player->pos.y - 8) / 16)    ;}
	if((surroundingSolids &  32) ==  32) {xTests[testIndex] = (int)(player->pos.x / 16) - 1; yTests[testIndex++] = (int)((player->pos.y - 8) / 16) + 1;}
	if((surroundingSolids &  64) ==  64) {xTests[testIndex] = (int)(player->pos.x / 16)    ; yTests[testIndex++] = (int)((player->pos.y - 8) / 16) + 1;}
	if((surroundingSolids & 128) == 128) {xTests[testIndex] = (int)(player->pos.x / 16) + 1; yTests[testIndex++] = (int)((player->pos.y - 8) / 16) + 1;}
	
	printf("\x1b[%d;%dH%i", (1 + 1), (36 + 1), getBit(surroundingSolids, 0));
	printf("\x1b[%d;%dH%i", (1 + 1), (37 + 1), getBit(surroundingSolids, 1));
	printf("\x1b[%d;%dH%i", (1 + 1), (38 + 1), getBit(surroundingSolids, 2));
	printf("\x1b[%d;%dH%i", (2 + 1), (36 + 1), getBit(surroundingSolids, 3));
	printf("\x1b[%d;%dH%i", (2 + 1), (38 + 1), getBit(surroundingSolids, 4));
	printf("\x1b[%d;%dH%i", (3 + 1), (36 + 1), getBit(surroundingSolids, 5));
	printf("\x1b[%d;%dH%i", (3 + 1), (37 + 1), getBit(surroundingSolids, 6));
	printf("\x1b[%d;%dH%i", (3 + 1), (38 + 1), getBit(surroundingSolids, 7));
}

void initPlayer(Player* player, int x, int y) {
	setVec2(&player->pos, x, y);
	setVec2(&player->vel, 0, 0);
	
	player->ground = 0;
	player->facing = 1;
	player->health = 0;
	player->deathTimer = 0;
	player->pTimer = 0;
	
	player->state = STATE_IDLE;
	player->animation = ANIM_IDLE;
	
	player->smallWalkAnim.sprites = marioSmallWalkSprites;
	player->smallWalkAnim.size = 2;
	player->smallWalkAnim.frame = 0;
	player->smallWalkAnim.frameStartTime = osGetTime();
	player->smallWalkAnim.frameLength = 50;
	
	player->smallRunAnim.sprites = marioSmallRunSprites;
	player->smallRunAnim.size = 2;
	player->smallRunAnim.frame = 0;
	player->smallRunAnim.frameStartTime = osGetTime();
	player->smallRunAnim.frameLength = 20;
	
	player->bigWalkAnim.sprites = marioBigWalkSprites;
	player->bigWalkAnim.size = 4;
	player->bigWalkAnim.frame = 0;
	player->bigWalkAnim.frameStartTime = osGetTime();
	player->bigWalkAnim.frameLength = 50;
	
	player->bigRunAnim.sprites = marioBigRunSprites;
	player->bigRunAnim.size = 4;
	player->bigRunAnim.frame = 0;
	player->bigRunAnim.frameStartTime = osGetTime();
	player->bigRunAnim.frameLength = 20;
	
	if(!player->jumpSound.allocated) {openSoundFile(&player->jumpSound, "romfs:/jump.raw", 0, 1);}
	player->jumpSound.fileEnd = 2;
}

void updatePlayer(Player* player, Tilemap tilemap, int timeDelta) {
	if(player->state != STATE_DEATH) {
		int surroundingSolids = checkSurroundingSolids((int)(player->pos.x / 16), (int)((player->pos.y - 8) / 16), tilemap, 200, 15);
		int surroundingPlatforms = checkSurroundingPlatforms((int)(player->pos.x / 16), (int)((player->pos.y - 8) / 16), tilemap, 200, 15);
		surroundingSolids += surroundingPlatforms;
		
		player->ground = false;
		if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(player->pos.x - 6, player->pos.y - 16, 12, 16.5f), getTileBB((int)(player->pos.x / 16) - 1, (int)((player->pos.y - 8) / 16) + 1))) {player->ground = true;}
		if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(player->pos.x - 6, player->pos.y - 16, 12, 16.5f), getTileBB((int)(player->pos.x / 16),     (int)((player->pos.y - 8) / 16) + 1))) {player->ground = true;}
		if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(player->pos.x - 6, player->pos.y - 16, 12, 16.5f), getTileBB((int)(player->pos.x / 16) + 1, (int)((player->pos.y - 8) / 16) + 1))) {player->ground = true;}
		if(player->vel.y < 0) {player->ground = false;}
		
		if(checkKeyHeld(KEY_LEFT) && !checkKeyHeld(KEY_RIGHT)) {
			if(player->ground) {
				if(player->vel.x <= 0) {
					if(!checkKeyHeld(KEY_B)) {player->vel.x -= WALK_ACCEL;}
					else {player->vel.x -= RUN_ACCEL;}
					
					if(player->state != STATE_RUN) {player->state = STATE_WALK;}
					if(player->state == STATE_LEAP) {player->state = STATE_RUN;}
				}
				else {
					player->vel.x -= SKID_ACCEL;
					player->state = STATE_SKID;
				}
			}
			else {
				if(!checkKeyHeld(KEY_B)) {player->vel.x -= WALK_ACCEL;}
				else {player->vel.x -= RUN_ACCEL;}
			}
			
			if(!checkKeyHeld(KEY_B)) {if(player->vel.x < -WALK_MAX_SPEED) {player->vel.x = -WALK_MAX_SPEED;}}
			else {if(player->vel.x < -RUN_MAX_SPEED) {player->vel.x = -RUN_MAX_SPEED;}}
			player->facing = -1;
		}
		if(checkKeyHeld(KEY_RIGHT) && !checkKeyHeld(KEY_LEFT)) {
			if(player->ground) {
				if(player->vel.x >= 0) {
					if(!checkKeyHeld(KEY_B)) {player->vel.x += WALK_ACCEL;}
					else {player->vel.x += RUN_ACCEL;}
					
					if(player->state != STATE_RUN) {player->state = STATE_WALK;}
					if(player->state == STATE_LEAP) {player->state = STATE_RUN;}
				}
				else {
					player->vel.x += SKID_ACCEL;
					player->state = STATE_SKID;
				}
			}
			else {
				if(!checkKeyHeld(KEY_B)) {player->vel.x += WALK_ACCEL;}
				else {player->vel.x += RUN_ACCEL;}
			}
			
			if(!checkKeyHeld(KEY_B)) {if(player->vel.x > WALK_MAX_SPEED) {player->vel.x = WALK_MAX_SPEED;}}
			else {if(player->vel.x > RUN_MAX_SPEED) {player->vel.x = RUN_MAX_SPEED;}}
			player->facing = 1;
		}
		if((!checkKeyHeld(KEY_LEFT) && !checkKeyHeld(KEY_RIGHT)) || (checkKeyHeld(KEY_LEFT) && checkKeyHeld(KEY_RIGHT))) {
			if(player->vel.x >= -WALK_ACCEL / 2.0f && player->vel.x <= WALK_ACCEL / 2.0f) {
				player->vel.x = 0;
				if(player->ground) {player->state = STATE_IDLE;}
			}
			else if(player->vel.x < 0) {player->vel.x += WALK_ACCEL;}
			else if(player->vel.x > 0) {player->vel.x -= WALK_ACCEL;}
		}
		
		if(player->ground) {
			if(checkKeyDown(KEY_A)) {
				player->vel.y = -JUMP_IMPULSE;
				
				if(player->state != STATE_RUN) {player->state = STATE_JUMP;}
				else {player->state = STATE_LEAP;}
				
				ndspChnWaveBufClear(1);
				ndspChnReset(1);
				ndspChnSetInterp(1, NDSP_INTERP_LINEAR);
				ndspChnSetRate(1, SAMPLERATE);
				ndspChnSetFormat(1, NDSP_FORMAT_STEREO_PCM16);
				
				player->jumpSound.fileEnd = 0;
				playSound(&player->jumpSound);
			}
			else {player->vel.y = 0;}
		}
		else {
			if(player->vel.y < 0) {
				if(checkKeyHeld(KEY_A) && player->vel.y < 0) {player->vel.y += GRAVITY;}
				else {player->vel.y += JUMP_STOP_GRAVITY;}
				if(player->state != STATE_LEAP) {player->state = STATE_JUMP;}
			}
			else {
				player->vel.y += GRAVITY;
				if(player->state != STATE_LEAP) {player->state = STATE_FALL;}
			}
		}
		
		player->pos.x += player->vel.x * timeDelta;
		player->pos.y += player->vel.y * timeDelta;
		
		surroundingSolids = checkSurroundingSolids((int)(player->pos.x / 16), (int)((player->pos.y - 8) / 16), tilemap, 200, 15);
		surroundingPlatforms = checkSurroundingPlatforms((int)(player->pos.x / 16), (int)((player->pos.y - 8) / 16), tilemap, 200, 15);
		
		int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
		int xTests[numTestSolids];
		int yTests[numTestSolids];
		getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, player);
		
		// change overlap algorithm:
		// when colliding, for each solid:
		// - convert to one dimensional data along movement vector (requires last position and current position, after movement)
		// - find first point along movement vector that doesn't collide
		// find smallest movement for every solid
		// after adjusting player's position, adjust velocity to fit the normal vector of the surface collided with
		// if new velocity is 0, stop here and do no further movement
		// move player along this new movement vector
		// check for collision, and repeat if collision found
		for(int i = 0; i < numTestSolids; i++) {
			if(checkBBOverlap(getBB(player->pos.x - 8, player->pos.y - 16, 16, 16), getTileBB(xTests[i], yTests[i]))) {
				Vec2 overlap = findSmallestOverlap(getBB(player->pos.x - 8, player->pos.y - 16, 16, 16), getTileBB(xTests[i], yTests[i]), surroundingSolids, player->vel, checkPlatform(getMapValue(tilemap, xTests[i], yTests[i])));
				
				player->pos.x -= overlap.x;
				player->pos.y -= overlap.y;
				consolePrint("COLLIDE", 0, 2);
				
				if(overlap.x != 0) {player->vel.x = 0;}
				if(overlap.y != 0) {player->vel.y = 0;}
				
				if(overlap.x != 0 && overlap.y != 0) {break;}
				
				if(overlap.y < 0 && overlap.x == 0) {
					for(int q = 0; q < MAX_OBJECTS; q++) {
						if(questionBlocks[q].xTile == xTests[i] && questionBlocks[q].yTile == yTests[i]) {
							startQuestionBlockBump(&questionBlocks[q]);
						}
					}
				}
				
				/*if(getMapValue(tilemap, xTests[i], yTests[i]) == 108 && overlap.y < 0 && overlap.x == 0) {
					setMapValue(&tilemap, xTests[i], yTests[i], -1);
					
					int partIndex = findFreeParticle();
					if(partIndex != -1) {initParticle(&particles[partIndex], questionBlockSprites, 3, 50, xTests[i] * 16, yTests[i] * 16 - 2);}
					
					int mushIndex = findFreeMushroom();
					if(mushIndex != -1) {initMushroom(&mushrooms[mushIndex], xTests[i] * 16 + 8, yTests[i] * 16);}
				}*/
			}
		}
		
		if(getMapValue(tilemap, (int)((player->pos.x - 8) / 16), (int)((player->pos.y - 16) / 16)) == 129) {
			setMapValue(&tilemap, (int)((player->pos.x - 8) / 16), (int)((player->pos.y - 16) / 16), -1);
		}
		if(getMapValue(tilemap, (int)((player->pos.x + 8) / 16), (int)((player->pos.y - 16) / 16)) == 129) {
			setMapValue(&tilemap, (int)((player->pos.x + 8) / 16), (int)((player->pos.y - 16) / 16), -1);
		}
		if(getMapValue(tilemap, (int)((player->pos.x + 8) / 16), (int)((player->pos.y) / 16)) == 129) {
			setMapValue(&tilemap, (int)((player->pos.x + 8) / 16), (int)((player->pos.y) / 16), -1);
		}
		if(getMapValue(tilemap, (int)((player->pos.x - 8) / 16), (int)((player->pos.y) / 16)) == 129) {
			setMapValue(&tilemap, (int)((player->pos.x - 8) / 16), (int)((player->pos.y) / 16), -1);
		}
		
		for(int i = 0; i < MAX_OBJECTS; i++) {
			if(goombas[i].exists) {
				if(checkBBOverlap(getBB(player->pos.x - 8, player->pos.y - 16, 16, 16), getGoombaBB(&goombas[i]))) {
					if(player->vel.y > 0) {
						goombas[i].exists = 0;
						player->vel.y = -0.3f;
					}
					else {player->state = STATE_DEATH;}
				}
			}
			if(mushrooms[i].exists) {
				if(checkBBOverlap(getBB(player->pos.x - 8, player->pos.y - 16, 16, 16), getMushroomBB(&mushrooms[i]))) {
					mushrooms[i].exists = 0;
					player->health = 1;
				}
			}
			if(piranhas[i].exists) {
				if(checkBBOverlap(getBB(player->pos.x - 8, player->pos.y - 16, 16, 16), getPiranhaBB(&piranhas[i]))) {
					player->state = STATE_DEATH;
				}
			}
		}
		
		/*if(px < 0) {px = 0;}
		if(px >= SCREEN_WIDTH - 16) {px = SCREEN_WIDTH - 16 - 1;}
		if(py >= SCREEN_HEIGHT - 24 - 32) {py = SCREEN_HEIGHT - 24 - 32 - 1;}*/
		
		if(player->vel.x == 0 && player->state == STATE_WALK) {player->state = STATE_IDLE;}
		
		if(fabs(player->vel.x) == RUN_MAX_SPEED) {
			player->pTimer++;
			if(player->pTimer > 100) {
				player->pTimer = 100;
				if(player->ground) {player->state = STATE_RUN;}
				else {player->state = STATE_LEAP;}
			}
		}
		else {
			player->pTimer--;
			if(player->pTimer < 0) {player->pTimer = 0;}
			
			if(player->state == STATE_RUN && fabs(player->vel.x) > 0) {player->state = STATE_WALK;}
			if(player->state == STATE_RUN && fabs(player->vel.x) == 0) {player->state = STATE_IDLE;}
			//if(player->state == STATE_LEAP) {player->state = STATE_WALK;}
		}
		
		if(player->pos.y >= SCREEN_HEIGHT) {player->state = STATE_DEATH;}
		
		printf("\x1b[%d;%dHP Timer: %i", (3 + 1), (0 + 1), player->pTimer);
	}
	else {
		player->deathTimer += timeDelta;
		if(player->deathTimer >= 500 + 1000) {
			player->vel.y += 0.2f;
			player->pos.y += player->vel.y;
		}
		else if(player->deathTimer >= 500) {
			player->vel.y = -5;
			player->pos.y += player->vel.y;
			player->deathTimer += 1000;
		}
		else {
			player->vel.y = 0;
		}
	}
}

void drawPlayer(Player* player, Vec2 camPos) {
	float speedMult = 0;
	
	if(player->state == STATE_IDLE && player->animation != ANIM_IDLE) {player->animation = ANIM_IDLE;}
	if(player->state == STATE_WALK && player->animation != ANIM_WALK) {
		player->smallWalkAnim.frame = 0;
		player->smallWalkAnim.frameStartTime = osGetTime();
		player->bigWalkAnim.frame = 2;
		player->bigWalkAnim.frameStartTime = osGetTime();
		
		player->animation = ANIM_WALK;
	}
	if(player->state == STATE_JUMP && player->animation != ANIM_JUMP) {player->animation = ANIM_JUMP;}
	if(player->state == STATE_FALL && player->animation != ANIM_FALL) {player->animation = ANIM_FALL;}
	if(player->state == STATE_DEATH && player->animation != ANIM_DEATH) {player->animation = ANIM_DEATH;}
	if(player->state == STATE_SKID && player->animation != ANIM_SKID) {player->animation = ANIM_SKID;}
	if(player->state == STATE_RUN && player->animation != ANIM_RUN) {
		player->smallRunAnim.frame = 0;
		player->smallRunAnim.frameStartTime = osGetTime();
		player->bigRunAnim.frame = 2;
		player->bigRunAnim.frameStartTime = osGetTime();
		
		player->animation = ANIM_RUN;
	}
	if(player->state == STATE_LEAP && player->animation != ANIM_LEAP) {player->animation = ANIM_LEAP;}
	
	if(player->animation == ANIM_IDLE) {
		if(!player->health) {drawSpriteScale(&marioSmallWalkSprites[1], player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
		else {drawSpriteScale(&marioBigWalkSprites[3], player->pos.x - 9 - camPos.x, player->pos.y - 28 - camPos.y, -player->facing, 1);}
	}
	if(player->animation == ANIM_WALK) {
		if(!player->health) {drawSpriteScale(&player->smallWalkAnim.sprites[player->smallWalkAnim.frame], player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
		else {drawSpriteScale(&player->bigWalkAnim.sprites[player->bigWalkAnim.frame], player->pos.x - 9 - camPos.x, player->pos.y - 28 - camPos.y, -player->facing, 1);}
		
		speedMult = WALK_MAX_SPEED / fabs(player->vel.x);
		if(speedMult < 1) {speedMult *= 0.8f;}
		//if(speedMult > 2) {speedMult = 2;}
		if(osGetTime() - player->smallWalkAnim.frameStartTime > player->smallWalkAnim.frameLength * speedMult) {
			player->smallWalkAnim.frame++;
			if(player->smallWalkAnim.frame >= player->smallWalkAnim.size) {player->smallWalkAnim.frame = 0;}
			player->smallWalkAnim.frameStartTime = osGetTime();
		}
		if(osGetTime() - player->bigWalkAnim.frameStartTime > player->bigWalkAnim.frameLength * speedMult) {
			player->bigWalkAnim.frame++;
			if(player->bigWalkAnim.frame >= player->bigWalkAnim.size) {player->bigWalkAnim.frame = 0;}
			player->bigWalkAnim.frameStartTime = osGetTime();
		}
	}
	if(player->animation == ANIM_JUMP) {
		if(!player->health) {drawSpriteScale(&marioSmallJumpSprite, player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
		else {drawSpriteScale(&marioBigJumpSprite, player->pos.x - 9 - camPos.x, player->pos.y - 28 - camPos.y, -player->facing, 1);}
	}
	if(player->animation == ANIM_FALL) {
		if(!player->health) {drawSpriteScale(&marioSmallJumpSprite, player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
		else {drawSpriteScale(&marioBigFallSprite, player->pos.x - 9 - camPos.x, player->pos.y - 28 - camPos.y, -player->facing, 1);}
	}
	if(player->animation == ANIM_DEATH) {drawSpriteScale(&marioSmallDeathSprite, player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
	if(player->animation == ANIM_SKID) {
		if(!player->health) {drawSpriteScale(&marioSmallSkidSprite, player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
		else {drawSpriteScale(&marioBigSkidSprite, player->pos.x - 9 - camPos.x, player->pos.y - 28 - camPos.y, -player->facing, 1);}
	}
	if(player->animation == ANIM_RUN) {
		if(!player->health) {drawSpriteScale(&player->smallRunAnim.sprites[player->smallRunAnim.frame], player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
		else {drawSpriteScale(&player->bigRunAnim.sprites[player->bigRunAnim.frame], player->pos.x - 9 - camPos.x, player->pos.y - 28 - camPos.y, -player->facing, 1);}
		
		if(osGetTime() - player->smallRunAnim.frameStartTime > player->smallRunAnim.frameLength) {
			player->smallRunAnim.frame++;
			if(player->smallRunAnim.frame >= player->smallRunAnim.size) {player->smallRunAnim.frame = 0;}
			player->smallRunAnim.frameStartTime = osGetTime();
		}
		if(osGetTime() - player->bigRunAnim.frameStartTime > player->bigRunAnim.frameLength) {
			player->bigRunAnim.frame++;
			if(player->bigRunAnim.frame >= player->bigRunAnim.size) {player->bigRunAnim.frame = 0;}
			player->bigRunAnim.frameStartTime = osGetTime();
		}
	}
	if(player->animation == ANIM_LEAP) {
		if(!player->health) {drawSpriteScale(&marioSmallLeapSprite, player->pos.x - 8 - camPos.x, player->pos.y - 16 - camPos.y, -player->facing, 1);}
		else {drawSpriteScale(&marioBigLeapSprite, player->pos.x - 9 - camPos.x, player->pos.y - 28 - camPos.y, -player->facing, 1);}
	}
	
	if(player->jumpSound.fileEnd < 2) {updateSound(&player->jumpSound);}
}

#endif