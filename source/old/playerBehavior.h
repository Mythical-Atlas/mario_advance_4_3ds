#ifndef PLAYER_BEHAVIOR_H
#define PLAYER_BEHAVIOR_H

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

#define STATE_IDLE  0
#define STATE_WALK  1
#define STATE_SKID  2
#define STATE_JUMP  3
#define STATE_FALL  4
#define STATE_DEATH 5
#define STATE_RUN   6
#define STATE_LEAP  7
#define STATE_DUCK  8
#define STATE_KICK  9
#define STATE_SPIN  10
#define STATE_PIPE  11

#define ANIM_IDLE  0
#define ANIM_WALK  1
#define ANIM_SKID  2
#define ANIM_JUMP  3
#define ANIM_FALL  4
#define ANIM_DEATH 5
#define ANIM_RUN   6
#define ANIM_LEAP  7
#define ANIM_DUCK  8
#define ANIM_KICK  9
#define ANIM_SPIN  10
#define ANIM_PIPE  11

#define CARRYING_NOTHING   0
#define CARRYING_SHELL_RED 1

#define WALK_ACCEL        0.003f
#define WALK_MAX_SPEED    0.08f
#define RUN_ACCEL         0.006f
#define RUN_MAX_SPEED     0.12f
#define SKID_ACCEL        0.01f
#define JUMP_IMPULSE      0.35f
#define JUMP_STOP_GRAVITY 0.05f
#define GRAVITY           0.015f
#define MAX_FALL_SPEED    0.1f

#define RACOON_LEAP_GRAVITY 0.01f
#define RACOON_LEAP_UPDRAFT 0.15f
#define RACOON_FALL_UPDRAFT 0.1f

#define PP_ADD    0.1f
#define PP_REMOVE 0.1f
#define PP_MAX    7

void playJumpSound(Player* player) {
	flushChannel(1);
	player->jumpSound.fileEnd = 0;
	playSound(&player->jumpSound);
}
void playStompSound(Player* player) {
	flushChannel(2);
	player->stompSound.fileEnd = 0;
	playSound(&player->stompSound);
}
void playBumpSound(Player* player) {
	flushChannel(2);
	player->bumpSound.fileEnd = 0;
	playSound(&player->bumpSound);
}
void playGrowSound(Player* player) {
	flushChannel(2);
	player->growSound.fileEnd = 0;
	playSound(&player->growSound);
}
void playCoinSound(Player* player) {
	flushChannel(3);
	player->coinSound.fileEnd = 0;
	playSound(&player->coinSound);
}

void trySetPlayerState(Player* player, int state) {
	// attempt to set state to *state*
	// certain states have higher priority
}

void playerTakeDamage(Player* player) {
    if(player->power != 0 && player->invincibleTimer == 0) {
        player->invincibleTimer = 3000;
        player->power--;
    }
    else if(player->invincibleTimer == 0) {player->state = STATE_DEATH;}
}

void checkPlayerGround(Player* player, Level* level) {
    int surroundingSolids = checkSurroundingSolids((int)(player->pos.x / 16), (int)((player->pos.y - getPlayerBB(player).h / 2) / 16), level);
    int surroundingPlatforms = checkSurroundingPlatforms((int)(player->pos.x / 16), (int)((player->pos.y - getPlayerBB(player).h / 2) / 16), level);
    if(player->vel.y >= 0) {surroundingSolids += surroundingPlatforms;}
    
    player->ground = false;
    if((surroundingSolids &  32) ==  32 && checkBBOverlap(getBB(player->pos.x - 6, player->pos.y, 12, 0.5f), getTileBB((int)(player->pos.x / 16) - 1, (int)((player->pos.y - getPlayerBB(player).h / 2) / 16) + 1))) {player->ground = true;}
    if((surroundingSolids &  64) ==  64 && checkBBOverlap(getBB(player->pos.x - 6, player->pos.y, 12, 0.5f), getTileBB((int)(player->pos.x / 16),     (int)((player->pos.y - getPlayerBB(player).h / 2) / 16) + 1))) {player->ground = true;}
    if((surroundingSolids & 128) == 128 && checkBBOverlap(getBB(player->pos.x - 6, player->pos.y, 12, 0.5f), getTileBB((int)(player->pos.x / 16) + 1, (int)((player->pos.y - getPlayerBB(player).h / 2) / 16) + 1))) {player->ground = true;}
}

void resetPlayerFromKick(Player* player) {
    if(player->state == STATE_KICK && player->kickTimer == 0) {
        if(player->ground) {
            if(player->vel.x == 0) {player->state = STATE_IDLE;}
            else if(fabs(player->vel.x) == RUN_MAX_SPEED && player->pTimer == PP_MAX) {player->state = STATE_RUN;}
            else {player->state = STATE_WALK;}
        }
        else {
            if(fabs(player->vel.x) == RUN_MAX_SPEED && player->pTimer == PP_MAX) {player->state = STATE_LEAP;}
            else {player->state = STATE_FALL;}
        }
    }
}

void handlePlayerPipe(Player* player, Level* level) {
    if(player->state != STATE_DUCK) {
        for(int p = 0; p < MAX_OBJECTS; p++) {
            if(pipeEntrances[p].exists) {
                if(checkBBOverlap(getPlayerBB(player), getPipeEntranceBB(&pipeEntrances[p]))) {
                    if(checkKeyHeld(KEY_DOWN) && player->ground && pipeEntrances[p].direction == 1) {
                        player->state = STATE_PIPE;
                        player->pipeDirection = 1;
                        player->pos.x = pipeEntrances[p].xTile * 16;
                        player->pos.y = pipeEntrances[p].yTile * 16;
                        player->pipeIndex = p;
                    }
                    if(checkKeyHeld(KEY_UP) && pipeEntrances[p].direction == -1) {
                        player->state = STATE_PIPE;
                        player->pipeDirection = -1;
                        player->pos.x = pipeEntrances[p].xTile * 16;
                        if(player->power == 0) {player->pos.y = pipeEntrances[p].yTile * 16 + 16;}
                        else {player->pos.y = pipeEntrances[p].yTile * 16 + 32;}
                        player->pipeIndex = p;
                    }
                }
            }
        }
    }
}

void handlePlayerDuck(Player* player) {
    if(player->state != STATE_SPIN) {
        if(checkKeyHeld(KEY_DOWN) && player->power > 0) {
            if(player->ground || player->state == STATE_DUCK) {
                player->state = STATE_DUCK;
                if(player->vel.x >= -WALK_ACCEL / 2.0f && player->vel.x <= WALK_ACCEL / 2.0f) {player->vel.x = 0;}
                else if(player->vel.x < 0) {player->vel.x += WALK_ACCEL;}
                else if(player->vel.x > 0) {player->vel.x -= WALK_ACCEL;}
            }
        }
        else {
            if(player->state != STATE_KICK) {
                if(player->ground) {
                    if(player->vel.x == 0) {player->state = STATE_IDLE;}
                    else if(fabs(player->vel.x) == RUN_MAX_SPEED && player->pTimer == PP_MAX) {player->state = STATE_RUN;}
                    else {player->state = STATE_WALK;}
                }
                else {
                    if(fabs(player->vel.x) == RUN_MAX_SPEED && player->pTimer == PP_MAX) {player->state = STATE_LEAP;}
                    else {player->state = STATE_FALL;}
                }
            }
        }
    }
}

void handlePlayerCarry(Player* player) {
    if(player->state != STATE_DUCK && player->state != STATE_SPIN) {
        if(!checkKeyHeld(KEY_B) && player->carrying == CARRYING_SHELL_RED) {
            player->carrying = CARRYING_NOTHING;
            player->state = STATE_KICK;
            player->kickTimer = 100;

            int shellIndex = findFreeShell();
            if(shellIndex != -1) {
                initShell(&shells[shellIndex], player->pos.x + 24 * player->facing, player->pos.y - 2);
                shells[shellIndex].moving = player->facing;
            }
        }
    }
}

void handlePlayerSpin(Player* player, Level* level) {
    if(player->state != STATE_DUCK && player->state != STATE_KICK) {
        if(player->state == STATE_SPIN) {
            /*if(player->vel.x >= -WALK_ACCEL / 2.0f && player->vel.x <= WALK_ACCEL / 2.0f) {player->vel.x = 0;}
            else if(player->vel.x < 0) {player->vel.x += WALK_ACCEL;}
            else if(player->vel.x > 0) {player->vel.x -= WALK_ACCEL;}*/

            if(player->spinTimer == 0) {
                if(player->ground) {
                    if(player->vel.x == 0) {player->state = STATE_IDLE;}
                    else if(fabs(player->vel.x) == RUN_MAX_SPEED && player->pTimer == PP_MAX) {player->state = STATE_RUN;}
                    else {player->state = STATE_WALK;}
                }
                else {
                    if(fabs(player->vel.x) == RUN_MAX_SPEED && player->pTimer == PP_MAX) {player->state = STATE_LEAP;}
                    else {player->state = STATE_FALL;}
                }
            }
        }
        else {
            if(checkKeyDown(KEY_B) && player->carrying == CARRYING_NOTHING && player->power == 2 && player->ground) {
                player->state = STATE_SPIN;
                player->spinTimer = 200;

                for(int q = 0; q < MAX_OBJECTS; q++) {
                    if(questionBlocks[q].exists && questionBlocks[q].xTile == (int)((player->pos.x + 16 * player->facing) / 16) && questionBlocks[q].yTile == (int)((player->pos.y - 8) / 16)) {
                        if(player->power == 0 && questionBlocks[q].contains == BLOCK_CONTAINS_FEATHER) {questionBlocks[q].contains = BLOCK_CONTAINS_MUSHROOM;}
                        startQuestionBlockBump(&questionBlocks[q]);
                        playBumpSound(player);
                        if(questionBlocks[q].contains == BLOCK_CONTAINS_COIN) {
                            player->coins++;
                            playCoinSound(player);
                        }
                    }
                    if(brickBlocks[q].exists && brickBlocks[q].xTile == (int)((player->pos.x + 16 * player->facing) / 16) && brickBlocks[q].yTile == (int)((player->pos.y - 8) / 16)) {
                        if(player->power > 0) {
                            destroyBrickBlock(&brickBlocks[q]);
                            setMapValue(level, brickBlocks[q].xTile, brickBlocks[q].yTile, -1);
                        }
                        playBumpSound(player);
                    }
                    if(goombas[q].exists) {
                        if(checkBBOverlap(getBB(player->pos.x - BIG_COLLISION_WIDTH / 2.0f + 16 * player->facing, player->pos.y - BIG_COLLISION_HEIGHT, BIG_COLLISION_WIDTH, BIG_COLLISION_HEIGHT), getGoombaBB(&goombas[q]))) {
                            squishGoomba(&goombas[q]);
                            playStompSound(player);
                        }
                    }
                    if(koopas[q].exists) {
                        if(checkBBOverlap(getBB(player->pos.x - BIG_COLLISION_WIDTH / 2.0f + 16 * player->facing, player->pos.y - BIG_COLLISION_HEIGHT, BIG_COLLISION_WIDTH, BIG_COLLISION_HEIGHT), getKoopaBB(&koopas[q]))) {
                            spawnShell(&koopas[q]);
                            playStompSound(player);
                        }
                    }
                }
            }
        }
    }
} 

void handlePlayerMovement(Player* player) {
    if(player->state != STATE_DUCK/* && player->state != STATE_SPIN*/) {
        if(checkKeyHeld(KEY_LEFT) && !checkKeyHeld(KEY_RIGHT)) {
            if(player->ground) {
                if(player->vel.x <= 0) {
                    if(!checkKeyHeld(KEY_B)) {player->vel.x -= WALK_ACCEL;}
                    else {player->vel.x -= RUN_ACCEL;}
                    
                    if(player->state != STATE_KICK && player->state != STATE_SPIN) {
                        if(player->state != STATE_RUN) {player->state = STATE_WALK;}
                        if(player->state == STATE_LEAP) {player->state = STATE_RUN;}
                    }
                }
                else {
                    player->vel.x -= SKID_ACCEL;
                    if(player->state != STATE_KICK && player->state != STATE_SPIN) {player->state = STATE_SKID;}
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
                    
                    if(player->state != STATE_KICK && player->state != STATE_SPIN) {
                        if(player->state != STATE_RUN) {player->state = STATE_WALK;}
                        if(player->state == STATE_LEAP) {player->state = STATE_RUN;}
                    }
                }
                else {
                    player->vel.x += SKID_ACCEL;
                    if(player->state != STATE_KICK && player->state != STATE_SPIN) {player->state = STATE_SKID;}
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
                if(player->ground && player->state != STATE_KICK && player->state != STATE_SPIN) {player->state = STATE_IDLE;}
            }
            else if(player->vel.x < 0) {player->vel.x += WALK_ACCEL;}
            else if(player->vel.x > 0) {player->vel.x -= WALK_ACCEL;}
        }
    }
}

void handlePlayerJump(Player* player) {
    if(player->ground) {
        if(checkKeyDown(KEY_A)) {
            player->vel.y = -JUMP_IMPULSE;
            
            if(player->state != STATE_DUCK && player->state != STATE_KICK) {
                if(player->state != STATE_RUN) {player->state = STATE_JUMP;}
                else {player->state = STATE_LEAP;}
            }
            
            playJumpSound(player);
        }
        else {player->vel.y = 0;}

        player->canUpdraft = 0;
        player->updraftTimer = 0;
    }
}

void handlePlayerGravity(Player* player) {
    if(!player->ground) {
        if(player->vel.y < 0) {
            if(player->power == 2 && (player->state == STATE_LEAP || player->updraftTimer != 0)) {
                if(checkKeyHeld(KEY_A) && player->vel.y < 0) {player->vel.y += RACOON_LEAP_GRAVITY;}
                else {player->vel.y += GRAVITY;}
            }
            else {
                if(checkKeyHeld(KEY_A) && player->vel.y < 0) {player->vel.y += GRAVITY;}
                else {player->vel.y += JUMP_STOP_GRAVITY;}
            }

            if(player->state != STATE_LEAP && player->state != STATE_DUCK) {player->state = STATE_JUMP;}
        }
        else {
            if(player->power == 2 && (player->state == STATE_LEAP || player->updraftTimer != 0)) {player->vel.y += RACOON_LEAP_GRAVITY;}
            else {player->vel.y += GRAVITY;}

            if(player->state != STATE_LEAP && player->state != STATE_DUCK) {player->state = STATE_FALL;}
        }
    }
}

void handlePlayerUpdraft(Player* player) {
    if(!player->ground) {
        if(player->power == 2) {
            if(checkKeyDown(KEY_A)) {
                if(player->canUpdraft) {
                    if(player->state == STATE_LEAP) {player->vel.y = -RACOON_LEAP_UPDRAFT;}
                    else {
                        player->vel.y -= RACOON_FALL_UPDRAFT;
                        if(player->vel.y < 0) {player->vel.y = 0;}
                    }

                    player->updraftTimer = 500;
                }
                player->canUpdraft = 0;
            }
            else {player->canUpdraft = 1;}
        }
        else {
            player->canUpdraft = 0;
            player->updraftTimer = 0;
        }
    }
}

void handlePlayerCollision(Player* player, Level* level) {
    int surroundingSolids = checkSurroundingSolids((int)(player->pos.x / 16), (int)((player->pos.y - getPlayerBB(player).h / 2) / 16), level);
    int surroundingPlatforms = checkSurroundingPlatforms((int)(player->pos.x / 16), (int)((player->pos.y - getPlayerBB(player).h / 2) / 16), level);
    
    int numTestSolids = getNumTests(surroundingSolids + surroundingPlatforms);
    int xTests[numTestSolids];
    int yTests[numTestSolids];
    getTestPositions(surroundingSolids + surroundingPlatforms, numTestSolids, xTests, yTests, player->pos.x, player->pos.y - getPlayerBB(player).h / 2);
    
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
        if(checkBBOverlap(getPlayerBB(player), getTileBB(xTests[i], yTests[i]))) {
            Vec2 overlap = findSmallestOverlap(getPlayerBB(player), getTileBB(xTests[i], yTests[i]), surroundingSolids, player->vel, checkPlatform(getMapValue(level, xTests[i], yTests[i])));
            
            player->pos.x -= overlap.x;
            player->pos.y -= overlap.y;
            //consolePrint("COLLIDE", 0, 2);
            
            if(overlap.x != 0) {player->vel.x = 0;}
            if(overlap.y != 0) {player->vel.y = 0;}
            
            if(overlap.x != 0 && overlap.y != 0) {break;}
            
            if(overlap.y < 0 && overlap.x == 0) {
                for(int q = 0; q < MAX_OBJECTS; q++) {
                    if(questionBlocks[q].exists && questionBlocks[q].xTile == xTests[i] && questionBlocks[q].yTile == yTests[i]) {
                        if(player->power == 0 && questionBlocks[q].contains == BLOCK_CONTAINS_FEATHER) {questionBlocks[q].contains = BLOCK_CONTAINS_MUSHROOM;}
                        startQuestionBlockBump(&questionBlocks[q]);
                        playBumpSound(player);
                        if(questionBlocks[q].contains == BLOCK_CONTAINS_COIN) {
                            player->coins++;
                            playCoinSound(player);
                        }
                    }
                    if(brickBlocks[q].exists && brickBlocks[q].xTile == xTests[i] && brickBlocks[q].yTile == yTests[i]) {
                        if(player->power > 0) {
                            destroyBrickBlock(&brickBlocks[q]);
                            setMapValue(level, brickBlocks[q].xTile, brickBlocks[q].yTile, -1);
                        }
                        playBumpSound(player);
                    }
                }
            }
        }
    }
}

void handlePlayerObjectInteractions(Player* player, int timeDelta) {
    for(int i = 0; i < MAX_OBJECTS; i++) {
        if(goombas[i].exists) {
            if(checkBBOverlap(getPlayerBB(player), getGoombaBB(&goombas[i]))) {
                if(player->vel.y - goombas[i].vel.y > 0) {
                    if(goombas[i].winged) {
                        goombas[i].winged = 0;
                        if(!goombas[i].ground) {goombas[i].vel.y = 0;}
                    }
                    else {
                        squishGoomba(&goombas[i]);
                        playStompSound(player);
                    }

                    player->vel.y = -0.3f;
                    player->pos.y -= 3;
                }
                else {playerTakeDamage(player);}
            }
        }
        if(mushrooms[i].exists) {
            if(checkBBOverlap(getPlayerBB(player), getMushroomBB(&mushrooms[i]))) {
                mushrooms[i].exists = 0;
                if(!mushrooms[i].life) {if(player->power < 1) {player->power = 1;}}
                else {player->lives++;}
                playGrowSound(player);
            }
        }
        if(feathers[i].exists) {
            if(checkBBOverlap(getPlayerBB(player), getFeatherBB(&feathers[i]))) {
                feathers[i].exists = 0;
                player->power = 2;
                playGrowSound(player);
            }
        }
        if(piranhas[i].exists) {
            if(checkBBOverlap(getPlayerBB(player), getPiranhaBB(&piranhas[i]))) {if(player->invincibleTimer == 0) {playerTakeDamage(player);}}
        }
        if(koopas[i].exists) {
            if(checkBBOverlap(getPlayerBB(player), getKoopaBB(&koopas[i]))) {
                if(player->vel.y - koopas[i].vel.y > 0) {
                    spawnShell(&koopas[i]);
                    player->vel.y = -0.3f;
                    player->pos.y -= 3;
                    playStompSound(player);
                }
                else {playerTakeDamage(player);}
            }
        }
        if(shells[i].exists) {
            if(checkBBOverlap(getPlayerBB(player), getShellBB(&shells[i]))) {
                if(player->vel.y - shells[i].vel.y > 0) {
                    if(shells[i].moving != 0) {shells[i].moving = 0;}
                    else {
                        if(player->pos.x <= shells[i].pos.x) {
                            shells[i].moving = 1;
                            shells[i].pos.x += 2 + fabs(player->vel.x) * timeDelta;
                        }
                        else {
                            shells[i].moving = -1;
                            shells[i].pos.x -= 2 + fabs(player->vel.x) * timeDelta;
                        }
                    }
                    player->vel.y = -0.3f;
                    player->pos.y -= 4;
                    playStompSound(player);
                }
                else if(player->vel.y == shells[i].vel.y && checkKeyHeld(KEY_B) && shells[i].moving == 0) {
                    shells[i].exists = 0;
                    player->carrying = CARRYING_SHELL_RED;
                }
                else {
                    if(shells[i].moving != 0) {playerTakeDamage(player);}
                    else {
                        if(player->pos.x <= shells[i].pos.x) {
                            shells[i].moving = 1;
                            shells[i].pos.x += 2 + fabs(player->vel.x) * timeDelta;
                        }
                        else {
                            shells[i].moving = -1;
                            shells[i].pos.x -= 2 + fabs(player->vel.x) * timeDelta;
                        }
                        playStompSound(player);
                    }
                }
            }
        }
        if(coins[i].exists) {
            if(checkBBOverlap(getPlayerBB(player), getCoinBB(&coins[i]))) {
                collectCoin(&coins[i]);
                player->coins++;
                playCoinSound(player);
            }
        }
    }
}

#endif