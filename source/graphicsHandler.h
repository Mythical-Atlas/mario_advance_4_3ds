#ifndef GRAPHICS_HANDLER_H
#define GRAPHICS_HANDLER_H

#include <citro2d.h>

#include "csimple.h"

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
C2D_Sprite goombaSprites[2];
C2D_Sprite mushroomSprites[1];

void loadGraphics() {
	imageSheet = C2D_SpriteSheetLoad("romfs:/gfx/images.t3x");
	if(!imageSheet) {svcBreak(USERBREAK_PANIC);}

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
	
	C2D_SpriteFromSheet(&goombaSprites[0], imageSheet, 147);
	C2D_SpriteFromSheet(&goombaSprites[1], imageSheet, 148);
	
	C2D_SpriteFromSheet(&mushroomSprites[0], imageSheet, 149);
	
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
}

#endif