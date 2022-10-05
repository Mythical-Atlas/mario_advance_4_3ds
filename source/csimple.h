#ifndef CGRAPH_H
#define CGRAPH_H

#include "audio.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

typedef struct {
	float x;
	float y;
} Vec2;

typedef struct {
	C2D_Sprite* sprites; // points to sprites loaded in main class at program start
	int size;
	int frame;
	u64 frameStartTime;
	int frameLength; // in ms
} Animation;

void setVec2(Vec2* target, float x, float y) {
	target->x = x;
	target->y =y;
}

bool getBit(int bits, int bit) {return (bits >> bit) & 1;}

void initLibs() {
	romfsInit();
	
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	
	ndspInit();
	ndspSetOutputMode(NDSP_OUTPUT_STEREO);
	
	ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
	ndspChnSetRate(0, SAMPLERATE);
	ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
	
	ndspChnSetInterp(1, NDSP_INTERP_LINEAR);
	ndspChnSetRate(1, SAMPLERATE);
	ndspChnSetFormat(1, NDSP_FORMAT_STEREO_PCM16);
	
	osSetSpeedupEnable(true);
}

void exitLibs() {
    ndspExit();
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
}

bool checkKeyDown(int key) {return (hidKeysDown() & key);}
bool checkKeyHeld(int key) {return (hidKeysHeld() & key);}
bool checkKeyUp(int key) {return (hidKeysUp() & key);}

void consolePrint(char* input, int x, int y) {printf("\x1b[%d;%dH%s", (y + 1), (x + 1), input);}

void drawSprite(C2D_Sprite* sprite, float x, float y) {
	C2D_SpriteSetPos(sprite, x, y);
	C2D_DrawSprite(sprite);
}
void drawSpriteScale(C2D_Sprite* sprite, float x, float y, float xScale, float yScale) {
	C2D_SpriteSetPos(sprite, x, y);
	C2D_SpriteSetScale(sprite, xScale, yScale);
	C2D_DrawSprite(sprite);
}

#endif