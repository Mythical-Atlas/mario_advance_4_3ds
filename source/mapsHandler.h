#ifndef MAPS_HANDLER_H
#define MAPS_HANDLER_H

#include "global.h"
#include "csimple.h"

int getMapValue(Tilemap tilemap, int x, int y) {return tilemap.map[x + y * tilemap.mapw];}
void setMapValue(Tilemap* tilemap, int x, int y, int value) {tilemap->map[x + y * tilemap->mapw] = value;}

void drawTilemap(Tilemap tilemap, Vec2 camPos, int tileAnimTimer) {
	for(int x = 0; x < tilemap.mapw; x++) {
		for(int y = 0; y < tilemap.maph; y++) {
			if(getMapValue(tilemap, x, y) != -1) {
				if(getMapValue(tilemap, x, y) == 108) {/*drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y) + tileAnimTimer], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);*/}
				else if(getMapValue(tilemap, x, y) == 129) {drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y) + tileAnimTimer], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);}
				else if(getMapValue(tilemap, x, y) == 171) {drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y) + tileAnimTimer], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);}
				else {drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y)], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);}
			}
		}
	}
}
void drawTilemapWithoutPipes(Tilemap tilemap, Vec2 camPos, int tileAnimTimer) {
	for(int x = 0; x < tilemap.mapw; x++) {
		for(int y = 0; y < tilemap.maph; y++) {
			if(
				getMapValue(tilemap, x, y) != -1 &&
				!(getMapValue(tilemap, x, y) >= 59 && getMapValue(tilemap, x, y) <= 62) &&
				!(getMapValue(tilemap, x, y) >= 80 && getMapValue(tilemap, x, y) <= 83)
			) {
				if(getMapValue(tilemap, x, y) == 108) {/*drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y) + tileAnimTimer], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);*/}
				else if(getMapValue(tilemap, x, y) == 129) {drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y) + tileAnimTimer], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);}
				else if(getMapValue(tilemap, x, y) == 171) {drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y) + tileAnimTimer], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);}
				else {drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y)], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);}
			}
		}
	}
}
void drawTilemapOnlyPipes(Tilemap tilemap, Vec2 camPos) {
	for(int x = 0; x < tilemap.mapw; x++) {
		for(int y = 0; y < tilemap.maph; y++) {
			if(
				(getMapValue(tilemap, x, y) >= 59 && getMapValue(tilemap, x, y) <= 62) ||
				(getMapValue(tilemap, x, y) >= 80 && getMapValue(tilemap, x, y) <= 83)
			) {drawSprite(&tilemap.tileSprites[getMapValue(tilemap, x, y)], x * tilemap.tilew - (int)camPos.x, y * tilemap.tileh - (int)camPos.y);}
		}
	}
}

#endif