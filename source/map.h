#ifndef MAP_H
#define MAP_H

#include "csimple.h"

typedef struct {
	C2D_Sprite* tileSprites;
	int tilew;
	int tileh;
	int* map;
	int mapw;
	int maph;
} Tilemap;

void drawTilemap(Tilemap map, Vec2 camPos, int tileAnimTimer) {
	for(int x = 0; x < map.mapw; x++) {
		for(int y = 0; y < map.maph; y++) {
			if(map.map[y + x * map.maph] != -1) {
				if(map.map[y + x * map.maph] == 108) {drawSprite(&map.tileSprites[map.map[y + x * map.maph] + tileAnimTimer], x * map.tilew - (int)camPos.x, y * map.tileh - (int)camPos.y);}
				else if(map.map[y + x * map.maph] == 129) {drawSprite(&map.tileSprites[map.map[y + x * map.maph] + tileAnimTimer], x * map.tilew - (int)camPos.x, y * map.tileh - (int)camPos.y);}
				else if(map.map[y + x * map.maph] == 171) {drawSprite(&map.tileSprites[map.map[y + x * map.maph] + tileAnimTimer], x * map.tilew - (int)camPos.x, y * map.tileh - (int)camPos.y);}
				else {drawSprite(&map.tileSprites[map.map[y + x * map.maph]], x * map.tilew - (int)camPos.x, y * map.tileh - (int)camPos.y);}
			}
		}
	}
}

#endif