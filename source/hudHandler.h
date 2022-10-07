#ifndef HUD_HANDLER_H
#define HUD_HANDLER_H

#include <citro2d.h>

#include "csimple.h"
#include "player.h"
#include "graphicsHandler.h"

void drawHUD(Player* player, Vec2* scroll) {
	scroll->x++;
	scroll->y++;
	
	if(scroll->x >= 512) {scroll->x = 0;}
	if(scroll->y >= 513) {scroll->y = 0;}
	
	drawSprite(&hudBGSprite, scroll->x - 512, scroll->y - 512);
	drawSprite(&hudBGSprite, scroll->x,       scroll->y - 512);
	drawSprite(&hudBGSprite, scroll->x - 512, scroll->y);
	drawSprite(&hudBGSprite, scroll->x,       scroll->y);
	drawSprite(&hudBaseSprite, 47, 41);
	drawSprite(&hudLogoSprite, 84, 62);
	drawSprite(&ppBaseSprite, 89, 190);
	
	if(player->pTimer > 0) {
		for(int i = 0; i < (int)player->pTimer && i < 6; i++) {drawSprite(&ppArrowSprite, 89 + i * 8, 191);}
		if(player->pTimer == PP_MAX) {drawSprite(&ppSprite, 137, 190);}
	}
}

#endif