#ifndef GLOBAL_H
#define GLOBAL_H

#include <citro2d.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define SAMPLERATE 16000
#define SAMPLESPERBUF SAMPLERATE
#define BYTESPERSAMPLE 4
#define BUFFER_SIZE SAMPLESPERBUF * BYTESPERSAMPLE

#define LEVEL_11        0
#define LEVEL_11_PIPE_0 1

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

typedef struct {
	char inputBuffer[BUFFER_SIZE];
	FILE* filePointer;
	bool fillBlock;
	u32* audioBuffer;
	ndspWaveBuf waveBuf[2];
	int fileEnd;
	int numLoops;
	bool allocated;
	int channel;
} AudioFile;

typedef struct {
	float x;
	float y;
	float w;
	float h;
} BoundBox;
/*
typedef struct {
	C2D_Sprite* tileSprites;
	int tilew;
	int tileh;
	int* map;
	int mapw;
	int maph;
} Tilemap; // replace with level
*/

typedef struct {
	int levelID;
	C2D_Sprite* tileSprites;
	C2D_Sprite* background;
	AudioFile* music;
	int* map;
	int mapw;
	int maph;
} Level;

typedef struct {
	Vec2 pos;
	Vec2 vel; // measured in pixels/ms
	
	bool ground;
	int facing; // 1 = right, -1 = left
	
	int power;
	bool canUpdraft;
	int carrying;
	int pipeDirection;
	bool shouldPipeTravel;
	int pipeIndex;

	int deathTimer;
	float pTimer;
	int invincibleTimer;
	int updraftTimer;
	int kickTimer;
	int spinTimer;
	int pipeTimer;
	
	int state;
	int animation;

	int coins;
	int lives;
	int points;
	
	Animation smallWalkAnim;
	Animation smallRunAnim;
	Animation bigWalkAnim;
	Animation bigRunAnim;
	Animation racoonWalkAnim;
	Animation racoonRunAnim;
	Animation racoonFallAnim;
	Animation racoonLeapAnim;
	Animation racoonSpinAnim;
	
	AudioFile jumpSound;
	AudioFile stompSound;
	AudioFile bumpSound;
	AudioFile growSound;
	AudioFile coinSound;
} Player;

typedef struct {
	Vec2 pos;
	Vec2 vel;
	Animation anim;
	bool exists;
	bool ground;
	int facing;
	bool shouldSpawnShell;
	bool winged;
	int jumpTimer;
} Koopa;

typedef struct {
	Vec2 pos;
	Vec2 vel;
	Animation anim;
	bool exists;
	bool ground;
	int moving;
	AudioFile stompSound;
	AudioFile bumpSound;
	AudioFile coinSound;
} Shell;

typedef struct {
	Vec2 pos;
	Vec2 vel;
	bool exists;
	int appearing;
	int facing;
	bool ground;
	int floatTimer;
} Feather;

typedef struct {
	int xTile;
	int yTile;
	bool exists;
	
	int contains;
	int facade;
	bool bumping;
	
	Animation anim;
	Animation bumpAnim;
} QuestionBlock;

typedef struct {
	int xTile;
	int yTile;
	bool exists;
	
	Animation anim;
} Coin;

typedef struct {
	Vec2 pos;
	Vec2 vel;
	Animation shuffleAnim;
	bool exists;
	int facing;
	bool ground;
	bool winged;
	int jumpTimer;
} Goomba;

typedef struct {
	Vec2 pos;
	Vec2 vel;
	bool exists;
	int appearing;
	int facing;
	bool ground;
	bool life;
} Mushroom;

typedef struct {
	Vec2 pos;
	Animation anim;
	bool exists;
} Particle;

typedef struct {
	Vec2 pos;
	Animation anim;
	bool exists;
	int riseTimer;
	int yOffset;
} Piranha;

typedef struct {
	int xTile;
	int yTile;
	bool exists;

	Animation anim;
} BrickBlock;

typedef struct {
	int xTile;
	int yTile;
	bool exists;
	
	int direction;
	int destLevel;
	int destPipe;
	bool enterable;
} PipeEntrance;

void setVec2(Vec2* target, float x, float y) {
	target->x = x;
	target->y = y;
}

void initAnimation(Animation* anim, C2D_Sprite* sprites, int size, int frame, u64 frameStartTime, int frameLength) {
	anim->sprites = sprites;
	anim->size = size;
	anim->frame = frame;
	anim->frameStartTime = frameStartTime;
	anim->frameLength = frameLength;
}
int getAnimFrame(Animation anim) {
	u64 elapsedSinceStartOfAnim = osGetTime() - anim.frameStartTime;
	u64 totalAnimationDuration = anim.frameLength * anim.size;
	u64 timePointInAnimation = elapsedSinceStartOfAnim % totalAnimationDuration;
	int frame = (int)(timePointInAnimation / anim.frameLength);

	return frame;
}

bool getBit(int bits, int bit) {return (bits >> bit) & 1;}

#endif