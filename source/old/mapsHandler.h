#ifndef MAPS_HANDLER_H
#define MAPS_HANDLER_H

#include "global.h"
#include "csimple.h"

int getMapValue(Level* level, int x, int y) {return level->map[x + y * level->mapw];}
void setMapValue(Level* level, int x, int y, int value) {level->map[x + y * level->mapw] = value;}

void drawTilemap(Level* level, Vec2 camPos) {
	for(int x = 0; x < level->mapw; x++) {
		for(int y = 0; y < level->maph; y++) {
			if(getMapValue(level, x, y) != -1) {
				if(getMapValue(level, x, y) == 108) {}
				else if(getMapValue(level, x, y) == 129) {}
				else if(getMapValue(level, x, y) == 171) {}
				else {drawSprite(&level->tileSprites[getMapValue(level, x, y)], x * 16 - (int)camPos.x, y * 16 - (int)camPos.y);}
			}
		}
	}
}
void drawTilemapWithoutPipes(Level* level, Vec2 camPos) {
	for(int x = 0; x < level->mapw; x++) {
		for(int y = 0; y < level->maph; y++) {
			if(
				getMapValue(level, x, y) != -1 &&
				!(getMapValue(level, x, y) >= 59 && getMapValue(level, x, y) <= 62) &&
				!(getMapValue(level, x, y) >= 80 && getMapValue(level, x, y) <= 83)
			) {
				if(getMapValue(level, x, y) == 108) {}
				else if(getMapValue(level, x, y) == 129) {}
				else if(getMapValue(level, x, y) == 171) {}
				else {drawSprite(&level->tileSprites[getMapValue(level, x, y)], x * 16 - (int)camPos.x, y * 16 - (int)camPos.y);}
			}
		}
	}
}
void drawTilemapOnlyPipes(Level* level, Vec2 camPos) {
	for(int x = 0; x < level->mapw; x++) {
		for(int y = 0; y < level->maph; y++) {
			if(
				(getMapValue(level, x, y) >= 59 && getMapValue(level, x, y) <= 62) ||
				(getMapValue(level, x, y) >= 80 && getMapValue(level, x, y) <= 83)
			) {drawSprite(&level->tileSprites[getMapValue(level, x, y)], x * 16 - (int)camPos.x, y * 16- (int)camPos.y);}
		}
	}
}

#endif