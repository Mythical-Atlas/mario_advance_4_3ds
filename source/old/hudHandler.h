#ifndef HUD_HANDLER_H
#define HUD_HANDLER_H

#include <citro2d.h>

#include "global.h"
#include "csimple.h"
#include "player.h"
#include "graphicsHandler.h"

void drawDigit(int num, int place, int x, int y, bool yellow) {drawSprite(&hudNumberSprites[
	(
		(num / (int)pow(10, place))
		% 10
	)
	+ 10 * (yellow == 1)
], x - 8 * place, y);}

void drawNumber(int num, int places, int x, int y, bool yellow) {
	if(places >= 1) {drawDigit(num, 0, x, y, yellow);}
	if(places >= 2) {drawDigit(num, 1, x, y, yellow);}
	if(places >= 3) {drawDigit(num, 2, x, y, yellow);}
	if(places >= 4) {drawDigit(num, 3, x, y, yellow);}
	if(places >= 5) {drawDigit(num, 4, x, y, yellow);}
	if(places >= 6) {drawDigit(num, 5, x, y, yellow);}
	if(places == 7) {drawDigit(num, 6, x, y, yellow);}
}

void drawHUD(Player* player, Vec2* scroll, int worldNum, int gameTime) {
	scroll->x++;
	scroll->y++;
	
	if(scroll->x >= 512) {scroll->x = 0;}
	if(scroll->y >= 513) {scroll->y = 0;}
	
	drawSprite(&hudBGSprite, scroll->x - 512, scroll->y - 512);
	drawSprite(&hudBGSprite, scroll->x,       scroll->y - 512);
	drawSprite(&hudBGSprite, scroll->x - 512, scroll->y);
	drawSprite(&hudBGSprite, scroll->x,       scroll->y);
	drawSprite(&hudBaseSprite, 47, 40);
	drawSprite(&hudLogoSprite, 84, 62);
	drawSprite(&ppBaseSprite, 89, 190);

	drawNumber(worldNum, 1, 72, 41, 1);
	drawNumber(gameTime, 3, 168, 41, 1);

	drawNumber(player->lives, 2, 120, 41, 0);
	drawNumber(player->coins, 2, 200, 41, 0);
	drawNumber(player->points, 7, 264, 41, 0);
	
	if(player->pTimer > 0) {
		for(int i = 0; i < (int)player->pTimer && i < 6; i++) {drawSprite(&ppArrowSprite, 89 + i * 8, 191);}
		if(player->pTimer == PP_MAX) {drawSprite(&ppSprite, 137, 190);}
	}
}

#endif