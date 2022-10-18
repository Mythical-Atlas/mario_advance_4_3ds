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

#define SONG_11 0
#define SONG_DEATH 1

Player player;

Vec2 camPos;
Vec2 hudBGScroll;

u64 tickStartTime;
int previousFrameDuration;
int numLongFrames;
int lastLongLength;

int songIndex;

int worldNum;
int gameTime;

AudioFile music;
AudioFile deathMusic;

int tileAnimTimer;
int tileAnimFrame;

void findObjectsInMap(Tilemap tilemap) {
	for(int x = 0; x < tilemap.mapw; x++) {
		for(int y = 0; y < tilemap.maph; y++) {
			int questIndex = findFreeQuestionBlock();
			if(questIndex != -1) {
				if(getMapValue(tilemap, x, y) == 1) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_MUSHROOM, BLOCK_FACADE_QUESTION);
					setMapValue(&tilemap, x, y, 108);
				}
				else if(getMapValue(tilemap, x, y) == 2) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_COIN, BLOCK_FACADE_QUESTION);
					setMapValue(&tilemap, x, y, 108);
				}
				else if(getMapValue(tilemap, x, y) == 108) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_NOTHING, BLOCK_FACADE_QUESTION);
					//setMapValue(&tilemap, x, y, -1);
				}
				else if(getMapValue(tilemap, x, y) == 154) {
					initQuestionBlock(&questionBlocks[questIndex], x, y, BLOCK_CONTAINS_NOTHING, BLOCK_FACADE_DEAD);
					//setMapValue(&tilemap, x, y, -1);
				}
			}

			int coinIndex = findFreeCoin();
			if(coinIndex != -1) {
				if(getMapValue(tilemap, x, y) == 129) {
					initCoin(&coins[coinIndex], x, y);
					setMapValue(&tilemap, x, y, -1);
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
	
	tileAnimTimer = 0;
	tileAnimFrame = 0;

	worldNum = 1;
	gameTime = 999;
	
	initLibs();
	
	loadGraphics();

	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	
	initObjects();
	initLevel11(&player);
	findObjectsInMap(level11Tilemap);
	
	openSoundFile(&music, "romfs:/music11.raw", 0, 0);
	openSoundFile(&deathMusic, "romfs:/death.raw", 0, 0);
	
	songIndex = SONG_11;
	
	playSound(&music);

	while(aptMainLoop()) {
		tickStartTime = osGetTime();
		
		hidScanInput();
		consoleClear();

		if(checkKeyDown(KEY_START)) {break;}
		
		gameTime = 999 - (int)((osGetTime() - startTime) / 1000);

		updatePlayer(&player, level11Tilemap, previousFrameDuration);
		camPos.x = player.pos.x - 200;
		if(camPos.x < 0) {camPos.x = 0;}
		
		updateObjects(level11Tilemap, previousFrameDuration);
		
		if(player.state == STATE_DEATH && songIndex != SONG_DEATH) {
			ndspChnWaveBufClear(0);
			ndspChnReset(0);
			ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
			ndspChnSetRate(0, SAMPLERATE);
			ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
	
			deathMusic.fileEnd = 0;
			playSound(&deathMusic);
			songIndex = SONG_DEATH;
		}
		
		consolePrint("Press start to exit", 0, 0);
		printf("\x1b[%d;%dHMilliseconds Elapsed: %llu", (1 + 1), (0 + 1), osGetTime() - startTime);
		printf("\x1b[%d;%dHPrevious Frame:     %i ms", (27 + 1), (0 + 1), previousFrameDuration);
		
		if(tileAnimTimer >= 100) {
			tileAnimFrame++;
			if(tileAnimFrame == 4) {tileAnimFrame = 0;}
			tileAnimTimer = 0;
		}
		
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);
		
		drawSprite(&bgSprite, -(((int)camPos.x / 2) % 512), 240 - 373);
		drawSprite(&bgSprite, -(((int)camPos.x / 2) % 512) + 512, 240 - 373);
		drawSprite(&bgSprite, -(((int)camPos.x / 2) % 512) + 512 * 2, 240 - 373);
		
		drawTilemapWithoutPipes(level11Tilemap, camPos, tileAnimFrame);
		
		drawObjects(camPos);
		
		drawTilemapOnlyPipes(level11Tilemap, camPos);

		drawPlayer(&player, camPos);
		
		C2D_TargetClear(bot, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(bot);
		
		drawHUD(&player, &hudBGScroll, worldNum, gameTime);
		
		C3D_FrameEnd(0);
		
		if(songIndex == SONG_11) {updateSound(&music);}
		else if(deathMusic.waveBuf[deathMusic.fillBlock].status == NDSP_WBUF_DONE && deathMusic.fileEnd == 2) {
			int oldLives = player.lives;

			initObjects();
			initLevel11(&player);
			findObjectsInMap(level11Tilemap);
			
			if(oldLives != 0) {player.lives = oldLives - 1;}
			else {break;}

			ndspChnWaveBufClear(0);
			ndspChnReset(0);
			ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
			ndspChnSetRate(0, SAMPLERATE);
			ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
			
			playSound(&music);
			songIndex = SONG_11;
		}
		else if(songIndex == SONG_DEATH) {updateSound(&deathMusic);}
		
		tileAnimTimer += previousFrameDuration;
		
		previousFrameDuration = osGetTime() - tickStartTime;
		if(previousFrameDuration >= 18) {
			numLongFrames++;
			lastLongLength = previousFrameDuration;
		}
	}

	C2D_SpriteSheetFree(imageSheet);

	if(music.allocated) {freeSound(&music);}
	if(player.jumpSound.allocated) {freeSound(&player.jumpSound);}

	exitLibs();
	
	return 0;
}