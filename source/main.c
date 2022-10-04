#include <citro2d.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "csimple.h"
#include "audio.h"
#include "collision.h"
#include "player.h"
#include "map.h"
#include "level11.h"
#include "question.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define SONG_11 0
#define SONG_DEATH 1

C2D_SpriteSheet imageSheet;

C2D_Sprite marioSmallWalkSprites[2];
C2D_Sprite marioSmallJumpSprites[1];
C2D_Sprite marioSmallSkidSprites[1];
C2D_Sprite marioSmallDeathSprites[1];
C2D_Sprite marioSmallRunSprites[2];
C2D_Sprite marioSmallLeapSprites[1];

C2D_Sprite marioBigWalkSprites[4];
C2D_Sprite marioBigJumpSprites[1];
C2D_Sprite marioBigFallSprites[1];
C2D_Sprite marioBigSkidSprites[1];
C2D_Sprite marioBigRunSprites[4];
C2D_Sprite marioBigLeapSprites[1];

C2D_Sprite bgSprite;

C2D_Sprite tileSprites[231];

C2D_Sprite questionBlockSprites[4];

Player player;
PlayerObjectInfo playerObjectInfo;

Vec2 camPos;

u64 tickStartTime;
int previousFrameDuration;
int numLongFrames;
int lastLongLength;

int songIndex;

AudioFile music;
AudioFile deathMusic;

QuestionBlock questionBlockObj;
bool questionObjExists;

int tileAnimTimer;
int tileAnimFrame;

int main(int argc, char* argv[]) {
	u64 startTime = osGetTime();
	previousFrameDuration = 17; // 60 fps is 16.67 ms per frame, so to get a nominal inital time delta, set to 16 or 17 ish
	numLongFrames = 0;
	lastLongLength = 0;
	
	questionObjExists = 0;
	
	tileAnimTimer = 0;
	tileAnimFrame = 0;
	
	initLibs();

	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	consoleInit(GFX_BOTTOM, NULL);

	imageSheet = C2D_SpriteSheetLoad("romfs:/gfx/images.t3x");
	if (!imageSheet) {svcBreak(USERBREAK_PANIC);}

	C2D_SpriteFromSheet(&marioSmallWalkSprites[0], imageSheet, 0);
	C2D_SpriteFromSheet(&marioSmallWalkSprites[1], imageSheet, 1);
	C2D_SpriteFromSheet(&marioSmallJumpSprites[0], imageSheet, 2);
	C2D_SpriteFromSheet(&marioSmallSkidSprites[0], imageSheet, 3);
	C2D_SpriteFromSheet(&marioSmallDeathSprites[0], imageSheet, 4);
	C2D_SpriteFromSheet(&marioSmallRunSprites[0], imageSheet, 5);
	C2D_SpriteFromSheet(&marioSmallRunSprites[1], imageSheet, 6);
	C2D_SpriteFromSheet(&marioSmallLeapSprites[0], imageSheet, 7);
	
	C2D_SpriteFromSheet(&marioBigWalkSprites[0], imageSheet, 8);
	C2D_SpriteFromSheet(&marioBigWalkSprites[1], imageSheet, 9);
	C2D_SpriteFromSheet(&marioBigWalkSprites[2], imageSheet, 10);
	C2D_SpriteFromSheet(&marioBigWalkSprites[3], imageSheet, 11);
	C2D_SpriteFromSheet(&marioBigJumpSprites[0], imageSheet, 12);
	C2D_SpriteFromSheet(&marioBigFallSprites[0], imageSheet, 13);
	C2D_SpriteFromSheet(&marioBigSkidSprites[0], imageSheet, 14);
	C2D_SpriteFromSheet(&marioBigRunSprites[0], imageSheet, 15);
	C2D_SpriteFromSheet(&marioBigRunSprites[1], imageSheet, 16);
	C2D_SpriteFromSheet(&marioBigRunSprites[2], imageSheet, 17);
	C2D_SpriteFromSheet(&marioBigRunSprites[3], imageSheet, 18);
	C2D_SpriteFromSheet(&marioBigLeapSprites[0], imageSheet, 19);
	
	C2D_SpriteFromSheet(&bgSprite, imageSheet, 20);
	
	C2D_SpriteFromSheet(&questionBlockSprites[0], imageSheet, 143);
	C2D_SpriteFromSheet(&questionBlockSprites[1], imageSheet, 144);
	C2D_SpriteFromSheet(&questionBlockSprites[2], imageSheet, 145);
	C2D_SpriteFromSheet(&questionBlockSprites[3], imageSheet, 146);
	
	int tileImageIndex = 21;
	for(int i =   7; i <=  16; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i =  26; i <=  37; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i =  47; i <=  62; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i =  68; i <=  83; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i =  89; i <= 100; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 108; i <= 112; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 114; i <= 121; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 129; i <= 133; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 135; i <= 142; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 154; i <= 163; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 168; i <= 174; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 177; i <= 181; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 198; i <= 202; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	for(int i = 219; i <= 221; i++) {C2D_SpriteFromSheet(&tileSprites[i], imageSheet, tileImageIndex++);}
	
	initLevel11(tileSprites);
	
	openSoundFile(&music, "romfs:/music11.raw", 0, 0);
	openSoundFile(&deathMusic, "romfs:/death.raw", 0, 0);
	
	songIndex = SONG_11;
	
	initPlayer(
		&player,
		marioSmallWalkSprites,
		marioSmallSkidSprites,
		marioSmallJumpSprites,
		marioSmallDeathSprites,
		marioSmallRunSprites,
		marioSmallLeapSprites,
		marioBigWalkSprites,
		marioBigSkidSprites,
		marioBigJumpSprites,
		marioBigFallSprites,
		marioBigRunSprites,
		marioBigLeapSprites
	);
	
	//playSound(&music);

	while(aptMainLoop()) {
		tickStartTime = osGetTime();
		
		hidScanInput();
		consoleClear();

		if(checkKeyDown(KEY_START)) {break;}
		
		updatePlayer(&player, map, previousFrameDuration, &playerObjectInfo);
		camPos.x = player.pos.x - 200;
		
		if(player.state == STATE_DEATH && songIndex != SONG_DEATH) {
			playSound(&deathMusic);
			songIndex = SONG_DEATH;
		}
		
		if(questionObjExists) {
			if(updateQuestionBlock(&questionBlockObj, previousFrameDuration)) {
				questionObjExists = 0;
				map[questionBlockObj.xTile][questionBlockObj.yTile] = 108;
			}
		}
		
		if(playerObjectInfo.hitQuestionBlock && !questionObjExists) {
			questionObjExists = 1;
			playerObjectInfo.hitQuestionBlock = 0;
			initQuestionBlock(&questionBlockObj, playerObjectInfo.qbx, playerObjectInfo.qby, questionBlockSprites);
			map[playerObjectInfo.qbx][playerObjectInfo.qby] = -1;
		}
		
		consolePrint("Press start to exit", 0, 0);
		
		printf("\x1b[%d;%dHMilliseconds Elapsed: %llu", (1 + 1), (0 + 1), osGetTime() - startTime);
		/*printf("\x1b[%d;%dHPlayer X: %f", (3 + 1), (0 + 1), px);
		printf("\x1b[%d;%dHPlayer Y: %f", (4 + 1), (0 + 1), py);*/
		//printf("\x1b[%d;%dHScroll: %f", (5 + 1), (0 + 1), scroll);
		//printf("\x1b[%d;%dHAdjusted Player X: %f", (6 + 1), (0 + 1), apx);
		
		printf("\x1b[%d;%dHGround: %i", (7 + 1), (0 + 1), player.ground);
		//printf("\x1b[%d;%dHSurrounding Solids: %i", (8 + 1), (0 + 1), surroundingSolids);
		
		//printf("\x1b[%d;%dHCh. 1 Buf Seq:    %i", (24 + 1), (0 + 1), ndspChnGetWaveBufSeq(1));
		//printf("\x1b[%d;%dHCh. 1 Sample Pos: %i", (25 + 1), (0 + 1), ndspChnGetSamplePos(1));
		
		//printf("\x1b[%d;%dHMax Time Per Frame: 16.67 ms", (26 + 1), (0 + 1));
		printf("\x1b[%d;%dHPrevious Frame:     %i ms", (27 + 1), (0 + 1), previousFrameDuration);
		//printf("\x1b[%d;%dHNumber of Long Frames: %i frames", (28 + 1), (0 + 1), numLongFrames);
		//printf("\x1b[%d;%dHPrevious Long Frame Length: %i ms", (29 + 1), (0 + 1), lastLongLength);
		
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
		
		drawTilemap(level11Tilemap, camPos, tileAnimFrame);
		
		if(questionObjExists) {drawSprite(&questionBlockObj.questionBumpAnim.sprites[questionBlockObj.questionBumpAnim.frame], questionBlockObj.xTile * 16 - (int)camPos.x, questionBlockObj.yTile * 16 - (int)camPos.y - 2);}
		
		/*for(int x = 0; x < 200; x++) {
			for(int y = 0; y < 15; y++) {
				if(map[x][y]) {
					drawSprite(&tileSprite, x * 16 + ((int)scroll % (200 * 16)), y * 16);
					drawSprite(&tileSprite, x * 16 + ((int)scroll % (200 * 16)) + 200 * 16, y * 16);
				}
			}
		}*/
		
		drawPlayer(&player, camPos);
		
		C3D_FrameEnd(0);
		
		/*if(waveBuf[fillBlock].status == NDSP_WBUF_DONE && fileEnd == 2) {
			// stop playing
		}
		else {updateSound(&music);}*/
		
		if(songIndex == SONG_11) {updateSound(&music);}
		if(deathMusic.waveBuf[deathMusic.fillBlock].status == NDSP_WBUF_DONE && deathMusic.fileEnd == 2) {
			songIndex = SONG_11;
			initPlayer(
				&player,
				marioSmallWalkSprites,
				marioSmallSkidSprites,
				marioSmallJumpSprites,
				marioSmallDeathSprites,
				marioSmallRunSprites,
				marioSmallLeapSprites,
				marioBigWalkSprites,
				marioBigSkidSprites,
				marioBigJumpSprites,
				marioBigFallSprites,
				marioBigRunSprites,
				marioBigLeapSprites
			);
			deathMusic.fileEnd = 0;
			playSound(&music);
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