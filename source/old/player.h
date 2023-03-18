#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>

#include "global.h"
#include "csimple.h"
#include "collision.h"
#include "goomba.h"
#include "mushroom.h"
#include "objectsHandler.h"
#include "graphicsHandler.h"
#include "questionBlock.h"
#include "particle.h"
#include "brickBlock.h"
#include "playerBehavior.h"

#define SMALL_SPRITES_PIVOT_X  8
#define SMALL_SPRITES_PIVOT_Y  16
#define SMALL_SPRITES_WIDTH    16
#define BIG_SPRITES_PIVOT_X    12
#define BIG_SPRITES_PIVOT_Y    28
#define BIG_SPRITES_WIDTH      22
#define RACOON_SPRITES_PIVOT_X 16
#define RACOON_SPRITES_PIVOT_Y 30
#define RACOON_SPRITES_WIDTH   31

void initPlayer(Player* player, int x, int y) {
	setVec2(&player->pos, x, y);
	setVec2(&player->vel, 0, 0);
	
	player->ground = 0;
	player->facing = 1;
	player->power = 0;
	player->canUpdraft = 0;
	player->pipeDirection = 0;
	player->shouldPipeTravel = 0;
	player->pipeIndex = 0;

	player->deathTimer = 0;
	player->pTimer = 0;
	player->invincibleTimer = 0;
	player->updraftTimer = 0;
	player->kickTimer = 0;
	player->spinTimer = 0;
	player->pipeTimer = 0;

	player->state = STATE_IDLE;
	player->animation = ANIM_IDLE;

	player->coins = 0;
	player->lives = 3;
	player->points = 0;

	player->carrying = CARRYING_NOTHING;
	
	initAnimation(&player->smallWalkAnim, marioSmallWalkSprites, 2, 0, osGetTime(), 50);
	initAnimation(&player->smallRunAnim, marioSmallRunSprites, 2, 0, osGetTime(), 20);
	initAnimation(&player->bigWalkAnim, marioBigWalkSprites, 4, 0, osGetTime(), 50);
	initAnimation(&player->bigRunAnim, marioBigRunSprites, 4, 0, osGetTime(), 20);
	initAnimation(&player->racoonWalkAnim, marioRacoonWalkSprites, 4, 0, osGetTime(), 50);
	initAnimation(&player->racoonRunAnim, marioRacoonRunSprites, 4, 0, osGetTime(), 20);
	initAnimation(&player->racoonFallAnim, marioRacoonFallSprites, 3, 0, osGetTime(), 50);
	initAnimation(&player->racoonLeapAnim, marioRacoonLeapSprites, 3, 0, osGetTime(), 50);
	initAnimation(&player->racoonSpinAnim, marioRacoonSpinSprites, 4, 0, osGetTime(), 50);
	
	if(!player->jumpSound.allocated) {openSoundFile(&player->jumpSound, "romfs:/jump.raw", 0, 1);}
	player->jumpSound.fileEnd = 2;
	if(!player->stompSound.allocated) {openSoundFile(&player->stompSound, "romfs:/stomp.raw", 0, 2);}
	player->stompSound.fileEnd = 2;
	if(!player->bumpSound.allocated) {openSoundFile(&player->bumpSound, "romfs:/bump.raw", 0, 2);}
	player->bumpSound.fileEnd = 2;
	if(!player->growSound.allocated) {openSoundFile(&player->growSound, "romfs:/grow.raw", 0, 2);}
	player->growSound.fileEnd = 2;
	if(!player->coinSound.allocated) {openSoundFile(&player->coinSound, "romfs:/coin.raw", 0, 3);}
	player->coinSound.fileEnd = 2;
}

void updatePlayer(Player* player, Level* level, int timeDelta) {
	if(player->state != STATE_DEATH && player->state != STATE_PIPE) {
        checkPlayerGround(player, level);

        resetPlayerFromKick(player);

		handlePlayerPipe(player, level);

		if(player->state != STATE_PIPE) {
			handlePlayerDuck(player);

			handlePlayerCarry(player);

			handlePlayerSpin(player, level);

			handlePlayerMovement(player);

			handlePlayerJump(player);

			handlePlayerGravity(player);

			handlePlayerUpdraft(player);

			player->pos.x += player->vel.x * timeDelta;
			player->pos.y += player->vel.y * timeDelta;

			if(player->pos.x < 8) {
				player->pos.x = 8;
				player->vel.x = 0;
			}
			
			handlePlayerCollision(player, level);
			
			handlePlayerObjectInteractions(player, timeDelta);
			
			if(player->state != STATE_DEATH) {
				if(player->vel.x == 0 && player->state == STATE_WALK) {player->state = STATE_IDLE;}
				
				if(fabs(player->vel.x) == RUN_MAX_SPEED) {
					player->pTimer += PP_ADD;
					if(player->pTimer > PP_MAX) {
						player->pTimer = PP_MAX;
						if(player->ground) {player->state = STATE_RUN;}
						else {player->state = STATE_LEAP;}
					}
				}
				else {
					player->pTimer -= PP_REMOVE;
					if(player->pTimer < 0) {player->pTimer = 0;}
					
					if(player->state == STATE_RUN && fabs(player->vel.x) > 0) {player->state = STATE_WALK;}
					if(player->state == STATE_RUN && fabs(player->vel.x) == 0) {player->state = STATE_IDLE;}
					//if(player->state == STATE_LEAP) {player->state = STATE_WALK;}
				}
			}
			
			if(player->pos.y > level->maph * 16) {
				player->state = STATE_DEATH;
				player->invincibleTimer = 0;
			}
			
			//printf("\x1b[%d;%dHP Timer: %i", (3 + 1), (0 + 1), player->pTimer);

			if(player->invincibleTimer > 0) {player->invincibleTimer -= timeDelta;}
			if(player->invincibleTimer < 0) {player->invincibleTimer = 0;}

			if(player->updraftTimer > 0) {player->updraftTimer -= timeDelta;}
			if(player->updraftTimer < 0) {player->updraftTimer = 0;}

			if(player->kickTimer > 0) {player->kickTimer -= timeDelta;}
			if(player->kickTimer < 0) {player->kickTimer = 0;}

			if(player->spinTimer > 0) {player->spinTimer -= timeDelta;}
			if(player->spinTimer < 0) {player->spinTimer = 0;}
		}
	}
	else if(player->state == STATE_PIPE) {
		player->pipeTimer += timeDelta;
		if(player->pipeTimer >= 1300) {player->shouldPipeTravel = 1;}
	}
	else if(player->state == STATE_DEATH) {
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
		player->racoonWalkAnim.frame = 2;
		player->racoonWalkAnim.frameStartTime = osGetTime();
		
		player->animation = ANIM_WALK;
	}
	if(player->state == STATE_JUMP && player->animation != ANIM_JUMP) {player->animation = ANIM_JUMP;}
	if(player->state == STATE_FALL && player->animation != ANIM_FALL) {
		player->racoonFallAnim.frame = 0;
		player->racoonFallAnim.frameStartTime = osGetTime();

		player->animation = ANIM_FALL;
	}
	if(player->state == STATE_DEATH && player->animation != ANIM_DEATH) {player->animation = ANIM_DEATH;}
	if(player->state == STATE_SKID && player->animation != ANIM_SKID) {player->animation = ANIM_SKID;}
	if(player->state == STATE_RUN && player->animation != ANIM_RUN) {
		player->smallRunAnim.frame = 0;
		player->smallRunAnim.frameStartTime = osGetTime();
		player->bigRunAnim.frame = 2;
		player->bigRunAnim.frameStartTime = osGetTime();
		player->racoonRunAnim.frame = 2;
		player->racoonRunAnim.frameStartTime = osGetTime();
		
		player->animation = ANIM_RUN;
	}
	if(player->state == STATE_LEAP && player->animation != ANIM_LEAP) {
		player->racoonLeapAnim.frame = 2;
		player->racoonLeapAnim.frameStartTime = osGetTime();

		player->animation = ANIM_LEAP;
	}
	if(player->state == STATE_DUCK && player->animation != ANIM_DUCK) {player->animation = ANIM_DUCK;}
	if(player->state == STATE_KICK && player->animation != ANIM_KICK) {player->animation = ANIM_KICK;}
	if(player->state == STATE_SPIN && player->animation != ANIM_SPIN) {
		player->racoonSpinAnim.frame = 0;
		player->racoonSpinAnim.frameStartTime = osGetTime();

		player->animation = ANIM_SPIN;
	}
	if(player->state == STATE_PIPE && player->animation != ANIM_PIPE) {player->animation = ANIM_PIPE;}

	if(player->carrying == CARRYING_SHELL_RED) {drawSprite(&shellRedSprites[0], (int)player->pos.x - (int)camPos.x - 8 + 12 * player->facing, (int)player->pos.y - (int)camPos.y - 18);}

	int smallPivot = SMALL_SPRITES_PIVOT_X;
	int bigPivot = BIG_SPRITES_PIVOT_X;
	int racoonPivot = RACOON_SPRITES_PIVOT_X;

	if(player->facing == 1) {
		smallPivot = SMALL_SPRITES_WIDTH - SMALL_SPRITES_PIVOT_X;
		bigPivot = BIG_SPRITES_WIDTH - BIG_SPRITES_PIVOT_X;
		racoonPivot = RACOON_SPRITES_WIDTH - RACOON_SPRITES_PIVOT_X;
	}

	if(player->animation == ANIM_IDLE) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->carrying == CARRYING_NOTHING) {
				if(player->power == 0) {drawSpriteScale(&marioSmallWalkSprites[1], player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&marioBigWalkSprites[3], player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&marioRacoonWalkSprites[3], player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			}
			else {
				if(player->power == 0) {drawSpriteScale(&marioSmallWalkCarrySprites[1], player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&marioBigWalkCarrySprites[3], player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&marioRacoonWalkCarrySprites[3], player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			}
		}
	}
	if(player->animation == ANIM_WALK) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->carrying == CARRYING_NOTHING) {
				if(player->power == 0) {drawSpriteScale(&player->smallWalkAnim.sprites[player->smallWalkAnim.frame], player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&player->bigWalkAnim.sprites[player->bigWalkAnim.frame], player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&player->racoonWalkAnim.sprites[player->bigWalkAnim.frame], player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			}
			else {
				if(player->power == 0) {drawSpriteScale(&marioSmallWalkCarrySprites[player->smallWalkAnim.frame], player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&marioBigWalkCarrySprites[player->bigWalkAnim.frame], player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&marioRacoonWalkCarrySprites[player->bigWalkAnim.frame], player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			}
		}

		speedMult = WALK_MAX_SPEED / fabs(player->vel.x);
		if(speedMult < 1) {speedMult *= 0.8f;}
		//if(speedMult > 2) {speedMult = 2;}
		if(osGetTime() - player->smallWalkAnim.frameStartTime > player->smallWalkAnim.frameLength * speedMult) {
			player->smallWalkAnim.frame++;
			if(player->smallWalkAnim.frame >= player->smallWalkAnim.size) {player->smallWalkAnim.frame = 0;}
			player->smallWalkAnim.frameStartTime = osGetTime();// -= player->smallWalkAnim.frameLength * speedMult;
		}
		if(osGetTime() - player->bigWalkAnim.frameStartTime > player->bigWalkAnim.frameLength * speedMult) {
			player->bigWalkAnim.frame++;
			if(player->bigWalkAnim.frame >= player->bigWalkAnim.size) {player->bigWalkAnim.frame = 0;}
			player->bigWalkAnim.frameStartTime = osGetTime();// -= player->bigWalkAnim.frameLength * speedMult;
		}
		if(osGetTime() - player->racoonWalkAnim.frameStartTime > player->racoonWalkAnim.frameLength * speedMult) {
			player->racoonWalkAnim.frame++;
			if(player->racoonWalkAnim.frame >= player->racoonWalkAnim.size) {player->racoonWalkAnim.frame = 0;}
			player->racoonWalkAnim.frameStartTime = osGetTime();// -= player->racoonWalkAnim.frameLength * speedMult;
		}
	}
	if(player->animation == ANIM_JUMP) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->carrying == CARRYING_NOTHING) {
				if(player->power == 0) {drawSpriteScale(&marioSmallJumpSprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&marioBigJumpSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&marioRacoonJumpSprite, player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			}
			else {
				if(player->power == 0) {drawSpriteScale(&marioSmallJumpCarrySprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&marioBigJumpCarrySprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&marioRacoonJumpCarrySprite, player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			}
		}
	}
	if(player->animation == ANIM_FALL) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->carrying == CARRYING_NOTHING) {
				if(player->power == 0) {drawSpriteScale(&marioSmallJumpSprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&marioBigFallSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&player->racoonFallAnim.sprites[player->racoonFallAnim.frame], player->pos.x - racoonPivot - camPos.x, player->pos.y - 30 - camPos.y, -player->facing, 1);}
			}
			else {
				if(player->power == 0) {drawSpriteScale(&marioSmallJumpCarrySprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 1) {drawSpriteScale(&marioBigJumpCarrySprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
				else if(player->power == 2) {drawSpriteScale(&marioRacoonJumpCarrySprite, player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			}
		}

		/*if(osGetTime() - player->racoonFallAnim.frameStartTime > player->racoonFallAnim.frameLength) {
			player->racoonFallAnim.frame++;
			if(player->racoonFallAnim.frame >= player->racoonFallAnim.size) {player->racoonFallAnim.frame = 0;}
			player->racoonFallAnim.frameStartTime = osGetTime();
		}*/
	}
	if(player->animation == ANIM_DEATH) {if(player->invincibleTimer % 300 < 150) {drawSpriteScale(&marioSmallDeathSprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}}
	if(player->animation == ANIM_SKID) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->power == 0) {drawSpriteScale(&marioSmallSkidSprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 1) {drawSpriteScale(&marioBigSkidSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 2) {drawSpriteScale(&marioRacoonSkidSprite, player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
		}
	}
	if(player->animation == ANIM_RUN) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->power == 0) {drawSpriteScale(&player->smallRunAnim.sprites[player->smallRunAnim.frame], player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 1) {drawSpriteScale(&player->bigRunAnim.sprites[player->bigRunAnim.frame], player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 2) {drawSpriteScale(&player->racoonRunAnim.sprites[player->racoonRunAnim.frame], player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
		}

		if(osGetTime() - player->smallRunAnim.frameStartTime > player->smallRunAnim.frameLength) {
			player->smallRunAnim.frame++;
			if(player->smallRunAnim.frame >= player->smallRunAnim.size) {player->smallRunAnim.frame = 0;}
			player->smallRunAnim.frameStartTime = osGetTime();// -= player->smallRunAnim.frameLength;
		}
		if(osGetTime() - player->bigRunAnim.frameStartTime > player->bigRunAnim.frameLength) {
			player->bigRunAnim.frame++;
			if(player->bigRunAnim.frame >= player->bigRunAnim.size) {player->bigRunAnim.frame = 0;}
			player->bigRunAnim.frameStartTime = osGetTime();// -= player->bigRunAnim.frameLength;
		}
		if(osGetTime() - player->racoonRunAnim.frameStartTime > player->racoonRunAnim.frameLength) {
			player->racoonRunAnim.frame++;
			if(player->racoonRunAnim.frame >= player->racoonRunAnim.size) {player->racoonRunAnim.frame = 0;}
			player->racoonRunAnim.frameStartTime = osGetTime();// -= player->racoonRunAnim.frameLength;
		}
	}
	if(player->animation == ANIM_LEAP) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->power == 0) {drawSpriteScale(&marioSmallLeapSprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 1) {drawSpriteScale(&marioBigLeapSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 2) {drawSpriteScale(&player->racoonLeapAnim.sprites[player->racoonLeapAnim.frame], player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
		}

		/*if(osGetTime() - player->racoonLeapAnim.frameStartTime > player->racoonLeapAnim.frameLength) {
			player->racoonLeapAnim.frame++;
			if(player->racoonLeapAnim.frame >= player->racoonLeapAnim.size) {player->racoonLeapAnim.frame = 0;}
			player->racoonLeapAnim.frameStartTime = osGetTime();
		}*/
	}
	if(player->animation == ANIM_DUCK) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->power == 1) {drawSpriteScale(&marioBigDuckSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 2) {drawSpriteScale(&marioRacoonDuckSprite, player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
		}
	}
	if(player->animation == ANIM_KICK) {
		if(player->invincibleTimer % 300 < 150) {
			if(player->power == 0) {drawSpriteScale(&marioSmallKickSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 1) {drawSpriteScale(&marioBigKickSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
			else if(player->power == 2) {drawSpriteScale(&marioRacoonKickSprite, player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}
		}
	}
	if(player->animation == ANIM_SPIN) {
		if(player->invincibleTimer % 300 < 150) {drawSpriteScale(&player->racoonSpinAnim.sprites[player->racoonSpinAnim.frame], player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y, -player->facing, 1);}

		if(osGetTime() - player->racoonSpinAnim.frameStartTime > player->racoonSpinAnim.frameLength) {
			player->racoonSpinAnim.frame++;
			if(player->racoonSpinAnim.frame >= player->racoonSpinAnim.size) {player->racoonSpinAnim.frame = 0;}
			player->racoonSpinAnim.frameStartTime = osGetTime();
		}
	}
	if(player->animation == ANIM_PIPE) {
		int pipePos = (int)(player->pipeTimer / 50) * player->pipeDirection;

		if(player->invincibleTimer % 300 < 150) {
			if(player->power == 0) {drawSpriteScale(&marioSmallPipeSprite, player->pos.x - smallPivot - camPos.x, player->pos.y - SMALL_SPRITES_PIVOT_Y - camPos.y + pipePos, -player->facing, 1);}
			else if(player->power == 1) {drawSpriteScale(&marioBigPipeSprite, player->pos.x - bigPivot - camPos.x, player->pos.y - BIG_SPRITES_PIVOT_Y - camPos.y + pipePos, -player->facing, 1);}
			else if(player->power == 2) {drawSpriteScale(&marioRacoonPipeSprite, player->pos.x - racoonPivot - camPos.x, player->pos.y - RACOON_SPRITES_PIVOT_Y - camPos.y + pipePos, -player->facing, 1);}
		}
	}
	
	if(player->jumpSound.fileEnd < 2) {updateSound(&player->jumpSound);}
	if(player->stompSound.fileEnd < 2) {updateSound(&player->stompSound);}
	if(player->bumpSound.fileEnd < 2) {updateSound(&player->bumpSound);}
	if(player->growSound.fileEnd < 2) {updateSound(&player->growSound);}
}

#endif