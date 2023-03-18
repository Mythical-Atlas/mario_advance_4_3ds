#include <citro2d.h>
#include <3ds.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "csimple.h"
#include "audio.h"
#include "collision.h"
#include "mapsHandler.h"
#include "objectsHandler.h"
#include "hudHandler.h"
#include "player.h"
#include "level11.h"
#include "goomba.h"
#include "mushroom.h"
#include "particle.h"
#include "brickBlock.h"

Level* currentLevel;
Player player;

Vec2 camPos;
Vec2 hudBGScroll;

u64 tickStartTime;
int previousFrameDuration;
int numLongFrames;
int lastLongLength;

int worldNum;
int gameTime;

AudioFile deathMusic;
bool deathMusicPlaying;

void findObjectsInMap(Level* level) {
	for(int x = 0; x < level->mapw; x++) {
		for(int y = 0; y < level->maph; y++) {
			int questIndex = findFreeQuestionBlock();
			if(questIndex != -1) {
				if(getMapValue(level, x, y) == 1) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_MUSHROOM, BLOCK_FACADE_QUESTION);
					setMapValue(level, x, y, 108);
				}
				else if(getMapValue(level, x, y) == 2) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_COIN, BLOCK_FACADE_QUESTION);
					setMapValue(level, x, y, 108);
				}
				else if(getMapValue(level, x, y) == 3) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_FEATHER, BLOCK_FACADE_QUESTION);
					setMapValue(level, x, y, 108);
				}
				else if(getMapValue(level, x, y) == 4) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_1UP, BLOCK_FACADE_QUESTION);
					setMapValue(level, x, y, 108);
				}
				else if(getMapValue(level, x, y) == 22) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_1UP, BLOCK_FACADE_BRICK);
					setMapValue(level, x, y, 108);
				}
				else if(getMapValue(level, x, y) == 108) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_NOTHING, BLOCK_FACADE_QUESTION);
				}
				else if(getMapValue(level, x, y) == 154) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_NOTHING, BLOCK_FACADE_DEAD);
				}
			}

			int coinIndex = findFreeCoin();
			if(coinIndex != -1) {
				if(getMapValue(level, x, y) == 129) {
					initCoin(&coins[coinIndex], x, y);
					setMapValue(level, x, y, -1);
				}
			}

			int brickIndex = findFreeBrickBlock();
			if(brickIndex != -1) {
				if(getMapValue(level, x, y) == 171) {
					initBrickBlock(&brickBlocks[brickIndex], x, y);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	u64 startTime = osGetTime();
	previousFrameDuration = 17; // 60 fps is 16.67 ms per frame, so to get a nominal inital time delta, set to 16 or 17 ish
	numLongFrames = 0;
	lastLongLength = 0;
	
	setVec2(&hudBGScroll, 0, 0);

	worldNum = 1;
	gameTime = 999;

	deathMusicPlaying = 0;
	
	initLibs();
	
	loadGraphics();

	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	
	currentLevel = initWorld11(&player);
	flushChannel(0);
	playSound(currentLevel->music);
	findObjectsInMap(currentLevel);
	
	openSoundFile(&deathMusic, "romfs:/death.raw", 0, 0);

	while(aptMainLoop()) {
		tickStartTime = osGetTime();
		
		hidScanInput();
		consoleClear();

		if(checkKeyDown(KEY_START)) {break;}
		
		gameTime = 999 - (int)((osGetTime() - startTime) / 1000);

		if(player.shouldPipeTravel) {
			int newPipe = pipeEntrances[player.pipeIndex].destPipe;
			int oldLives = player.lives;
			int oldCoins = player.coins;
			int oldPoints = player.points;
			int oldPower = player.power;

			if(pipeEntrances[player.pipeIndex].destLevel == LEVEL_11) {currentLevel = initWorld11(&player);}
			else if(pipeEntrances[player.pipeIndex].destLevel == LEVEL_11_PIPE_0) {currentLevel = initWorld11Pipe0(&player);}

			player.pos.x = pipeEntrances[newPipe].xTile * 16;
			player.pos.y = pipeEntrances[newPipe].yTile * 16;

			player.lives = oldLives;
			player.coins = oldCoins;
			player.points = oldPoints;
			player.power = oldPower;

			if(pipeEntrances[newPipe].direction == -1) {
				if(player.power == 0) {player.pos.y += 16;}
				else {player.pos.y += 32;}
			}

			flushChannel(0);
			playSound(currentLevel->music);
			findObjectsInMap(currentLevel);
		}

		updatePlayer(&player, currentLevel, previousFrameDuration);
		camPos.x = player.pos.x - 200;
		if(camPos.x < 0) {camPos.x = 0;}
		if(camPos.x > currentLevel->mapw * 16 - SCREEN_WIDTH) {camPos.x = currentLevel->mapw * 16 - SCREEN_WIDTH;}
		camPos.y = player.pos.y - SCREEN_HEIGHT / 2;
		if(camPos.y < 0) {camPos.y = 0;}
		if(camPos.y > currentLevel->maph * 16 - SCREEN_HEIGHT) {camPos.y = currentLevel->maph * 16 - SCREEN_HEIGHT;}
		
		updateObjects(currentLevel, previousFrameDuration);
		
		if(player.state == STATE_DEATH && !deathMusicPlaying) {
			flushChannel(0);
			deathMusic.fileEnd = 0;
			playSound(&deathMusic);
			deathMusicPlaying = 1;
		}
		
		consolePrint("Press start to exit", 0, 0);
		printf("\x1b[%d;%dHMilliseconds Elapsed: %llu", (1 + 1), (0 + 1), osGetTime() - startTime);
		printf("\x1b[%d;%dHPrevious Frame:     %i ms", (27 + 1), (0 + 1), previousFrameDuration);
		
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);
		
		drawSprite(currentLevel->background, -(((int)camPos.x / 2) % 512), 240 - 373);
		drawSprite(currentLevel->background, -(((int)camPos.x / 2) % 512) + 512, 240 - 373);
		drawSprite(currentLevel->background, -(((int)camPos.x / 2) % 512) + 512 * 2, 240 - 373);
		
		drawTilemapWithoutPipes(currentLevel, camPos);
		
		drawObjects(camPos);
		
		drawPlayer(&player, camPos);

		drawTilemapOnlyPipes(currentLevel, camPos);
		
		C2D_TargetClear(bot, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(bot);
		
		drawHUD(&player, &hudBGScroll, worldNum, gameTime);
		
		C3D_FrameEnd(0);
		
		if(!deathMusicPlaying) {updateSound(currentLevel->music);}
		else if(deathMusic.waveBuf[deathMusic.fillBlock].status == NDSP_WBUF_DONE && deathMusic.fileEnd == 2) {
			int oldLives = player.lives;

			initWorld11(&player);
			currentLevel = &world11Level;
			flushChannel(0);
			playSound(currentLevel->music);
			findObjectsInMap(currentLevel);
			
			if(oldLives != 0) {player.lives = oldLives - 1;}
			else {break;}

			deathMusicPlaying = 0;
		}
		else if(deathMusicPlaying) {updateSound(&deathMusic);}

		previousFrameDuration = osGetTime() - tickStartTime;
		if(previousFrameDuration >= 18) {
			numLongFrames++;
			lastLongLength = previousFrameDuration;
		}
	}

	C2D_SpriteSheetFree(imageSheet);

	// FIX properly free all sound files
	if(currentLevel->music->allocated) {freeSound(currentLevel->music);}
	if(player.jumpSound.allocated) {freeSound(&player.jumpSound);}

	exitLibs();
	
	return 0;
}