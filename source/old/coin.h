#ifndef COIN_H
#define COIN_H

#include "global.h"
#include "csimple.h"
#include "graphicsHandler.h"
#include "objectsHandler.h"
#include "particle.h"

void initCoin(Coin* coin, int xTile, int yTile) {
	coin->xTile = xTile;
	coin->yTile = yTile;
	coin->exists = 1;
	
	initAnimation(&coin->anim, coinSprites, 4, 0, osGetTime(), 100);
	coin->anim.sprites = coinSprites;
	coin->anim.size = 4;
	coin->anim.frame = 0;
	coin->anim.frameStartTime = osGetTime();
	coin->anim.frameLength = 100;
}

void collectCoin(Coin* coin) {
	int partIndex = findFreeParticle();
	if(partIndex != -1) {initParticle(&particles[partIndex], coinCollectSprites, 3, 100, coin->xTile * 16 + 3, coin->yTile * 16);}
	coin->exists = 0;
}

void drawCoin(Coin* coin, Vec2 camPos) {
	if(osGetTime() - coin->anim.frameStartTime > coin->anim.frameLength) {
		coin->anim.frameStartTime = osGetTime();
		coin->anim.frame++;
		if(coin->anim.frame >= coin->anim.size) {coin->anim.frame = 0;}
	}

	drawSprite(&coin->anim.sprites[coin->anim.frame], coin->xTile * 16 - (int)camPos.x + 3, coin->yTile * 16 - (int)camPos.y);
}

BoundBox getCoinBB(Coin* coin) {
	BoundBox output;
	output.x = coin->xTile * 16;
	output.y = coin->yTile * 16;
	output.w = 16;
	output.h = 16;
	
	return output;
}

#endif