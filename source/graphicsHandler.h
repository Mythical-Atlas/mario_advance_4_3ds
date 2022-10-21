#ifndef GRAPHICS_HANDLER_H
#define GRAPHICS_HANDLER_H

#include <citro2d.h>

#include "global.h"
#include "csimple.h"

C2D_SpriteSheet imageSheet;

C2D_Sprite marioSmallWalkSprites[2];
C2D_Sprite marioSmallJumpSprite;
C2D_Sprite marioSmallSkidSprite;
C2D_Sprite marioSmallDeathSprite;
C2D_Sprite marioSmallRunSprites[2];
C2D_Sprite marioSmallLeapSprite;
C2D_Sprite marioSmallWalkCarrySprites[2];
C2D_Sprite marioSmallJumpCarrySprite;
C2D_Sprite marioSmallKickSprite;
C2D_Sprite marioSmallPipeSprite;

C2D_Sprite marioBigWalkSprites[4];
C2D_Sprite marioBigJumpSprite;
C2D_Sprite marioBigFallSprite;
C2D_Sprite marioBigSkidSprite;
C2D_Sprite marioBigRunSprites[4];
C2D_Sprite marioBigLeapSprite;
C2D_Sprite marioBigDuckSprite;
C2D_Sprite marioBigWalkCarrySprites[4];
C2D_Sprite marioBigJumpCarrySprite;
C2D_Sprite marioBigKickSprite;
C2D_Sprite marioBigPipeSprite;

C2D_Sprite marioRacoonWalkSprites[4];
C2D_Sprite marioRacoonJumpSprite;
C2D_Sprite marioRacoonFallSprites[3];
C2D_Sprite marioRacoonSkidSprite;
C2D_Sprite marioRacoonRunSprites[4];
C2D_Sprite marioRacoonLeapSprites[3];
C2D_Sprite marioRacoonDuckSprite;
C2D_Sprite marioRacoonWalkCarrySprites[4];
C2D_Sprite marioRacoonJumpCarrySprite;
C2D_Sprite marioRacoonKickSprite;
C2D_Sprite marioRacoonPipeSprite;
C2D_Sprite marioRacoonSpinSprites[4];

C2D_Sprite world11BGSprite;

C2D_Sprite tileSprites[231];

C2D_Sprite coinSprites[4];
C2D_Sprite mushroomSprite;
C2D_Sprite questionBlockBumpSprites[4];
C2D_Sprite goombaSprites[2];
C2D_Sprite goombaStompedSprite;
C2D_Sprite goombaWingsSprites[2];
C2D_Sprite koopaRedSprites[2];
C2D_Sprite koopaWingsSprites[2];
C2D_Sprite shellRedSprites[4];
C2D_Sprite piranhaRedGreenSprites[2];
C2D_Sprite coinCollectSprites[3];
C2D_Sprite coinBumpSprites[19];
C2D_Sprite questionBlockSprites[4];

C2D_Sprite hudNumberSprites[20];
C2D_Sprite hudBaseSprite;
C2D_Sprite hudBGSprite;
C2D_Sprite hudLogoSprite;
C2D_Sprite ppBaseSprite;
C2D_Sprite ppArrowSprite;
C2D_Sprite ppSprite;

C2D_Sprite featherSprite;

C2D_Sprite brickBlockSprites[4];

C2D_Sprite lifeShroomSprite;

void loadGraphics() {
	imageSheet = C2D_SpriteSheetLoad("romfs:/gfx/images.t3x");
	if(!imageSheet) {svcBreak(USERBREAK_PANIC);}

	C2D_SpriteFromSheet(&marioSmallWalkSprites[0], imageSheet, 0);
	C2D_SpriteFromSheet(&marioSmallWalkSprites[1], imageSheet, 1);
	C2D_SpriteFromSheet(&marioSmallJumpSprite, imageSheet, 2);
	C2D_SpriteFromSheet(&marioSmallSkidSprite, imageSheet, 3);
	C2D_SpriteFromSheet(&marioSmallDeathSprite, imageSheet, 4);
	C2D_SpriteFromSheet(&marioSmallRunSprites[0], imageSheet, 5);
	C2D_SpriteFromSheet(&marioSmallRunSprites[1], imageSheet, 6);
	C2D_SpriteFromSheet(&marioSmallLeapSprite, imageSheet, 7);
	
	C2D_SpriteFromSheet(&marioBigWalkSprites[0], imageSheet, 8);
	C2D_SpriteFromSheet(&marioBigWalkSprites[1], imageSheet, 9);
	C2D_SpriteFromSheet(&marioBigWalkSprites[2], imageSheet, 10);
	C2D_SpriteFromSheet(&marioBigWalkSprites[3], imageSheet, 11);
	C2D_SpriteFromSheet(&marioBigJumpSprite, imageSheet, 12);
	C2D_SpriteFromSheet(&marioBigFallSprite, imageSheet, 13);
	C2D_SpriteFromSheet(&marioBigSkidSprite, imageSheet, 14);
	C2D_SpriteFromSheet(&marioBigRunSprites[0], imageSheet, 15);
	C2D_SpriteFromSheet(&marioBigRunSprites[1], imageSheet, 16);
	C2D_SpriteFromSheet(&marioBigRunSprites[2], imageSheet, 17);
	C2D_SpriteFromSheet(&marioBigRunSprites[3], imageSheet, 18);
	C2D_SpriteFromSheet(&marioBigLeapSprite, imageSheet, 19);
	
	C2D_SpriteFromSheet(&world11BGSprite, imageSheet, 20);
	
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
	
	C2D_SpriteFromSheet(&coinSprites[0], imageSheet, 143);
	C2D_SpriteFromSheet(&coinSprites[1], imageSheet, 144);
	C2D_SpriteFromSheet(&coinSprites[2], imageSheet, 145);
	C2D_SpriteFromSheet(&coinSprites[3], imageSheet, 146);
	C2D_SpriteFromSheet(&mushroomSprite, imageSheet, 147);
	C2D_SpriteFromSheet(&questionBlockBumpSprites[0], imageSheet, 148);
	C2D_SpriteFromSheet(&questionBlockBumpSprites[1], imageSheet, 149);
	C2D_SpriteFromSheet(&questionBlockBumpSprites[2], imageSheet, 150);
	C2D_SpriteFromSheet(&questionBlockBumpSprites[3], imageSheet, 151);
	C2D_SpriteFromSheet(&goombaSprites[0], imageSheet, 152);
	C2D_SpriteFromSheet(&goombaSprites[1], imageSheet, 153);
	C2D_SpriteFromSheet(&goombaStompedSprite, imageSheet, 154);
	C2D_SpriteFromSheet(&goombaWingsSprites[0], imageSheet, 155);
	C2D_SpriteFromSheet(&goombaWingsSprites[1], imageSheet, 156);
	C2D_SpriteFromSheet(&koopaRedSprites[0], imageSheet, 157);
	C2D_SpriteFromSheet(&koopaRedSprites[1], imageSheet, 158);
	C2D_SpriteFromSheet(&koopaWingsSprites[0], imageSheet, 159);
	C2D_SpriteFromSheet(&koopaWingsSprites[1], imageSheet, 160);
	C2D_SpriteFromSheet(&shellRedSprites[0], imageSheet, 161);
	C2D_SpriteFromSheet(&shellRedSprites[1], imageSheet, 162);
	C2D_SpriteFromSheet(&shellRedSprites[2], imageSheet, 163);
	C2D_SpriteFromSheet(&shellRedSprites[3], imageSheet, 164);
	C2D_SpriteFromSheet(&piranhaRedGreenSprites[0], imageSheet, 165);
	C2D_SpriteFromSheet(&piranhaRedGreenSprites[1], imageSheet, 166);
	C2D_SpriteFromSheet(&coinCollectSprites[0], imageSheet, 167);
	C2D_SpriteFromSheet(&coinCollectSprites[1], imageSheet, 168);
	C2D_SpriteFromSheet(&coinCollectSprites[2], imageSheet, 169);
	C2D_SpriteFromSheet(&coinBumpSprites[0], imageSheet, 170);
	C2D_SpriteFromSheet(&coinBumpSprites[1], imageSheet, 171);
	C2D_SpriteFromSheet(&coinBumpSprites[2], imageSheet, 172);
	C2D_SpriteFromSheet(&coinBumpSprites[3], imageSheet, 173);
	C2D_SpriteFromSheet(&coinBumpSprites[4], imageSheet, 174);
	C2D_SpriteFromSheet(&coinBumpSprites[5], imageSheet, 175);
	C2D_SpriteFromSheet(&coinBumpSprites[6], imageSheet, 176);
	C2D_SpriteFromSheet(&coinBumpSprites[7], imageSheet, 177);
	C2D_SpriteFromSheet(&coinBumpSprites[8], imageSheet, 178);
	C2D_SpriteFromSheet(&coinBumpSprites[9], imageSheet, 179);
	C2D_SpriteFromSheet(&coinBumpSprites[10], imageSheet, 180);
	C2D_SpriteFromSheet(&coinBumpSprites[11], imageSheet, 181);
	C2D_SpriteFromSheet(&coinBumpSprites[12], imageSheet, 182);
	C2D_SpriteFromSheet(&coinBumpSprites[13], imageSheet, 183);
	C2D_SpriteFromSheet(&coinBumpSprites[14], imageSheet, 184);
	C2D_SpriteFromSheet(&coinBumpSprites[15], imageSheet, 185);
	C2D_SpriteFromSheet(&coinBumpSprites[16], imageSheet, 186);
	C2D_SpriteFromSheet(&coinBumpSprites[17], imageSheet, 187);
	C2D_SpriteFromSheet(&coinBumpSprites[18], imageSheet, 188);
	C2D_SpriteFromSheet(&questionBlockSprites[0], imageSheet, 189);
	C2D_SpriteFromSheet(&questionBlockSprites[1], imageSheet, 190);
	C2D_SpriteFromSheet(&questionBlockSprites[2], imageSheet, 191);
	C2D_SpriteFromSheet(&questionBlockSprites[3], imageSheet, 192);
	
	C2D_SpriteFromSheet(&hudNumberSprites[0], imageSheet, 193);
	C2D_SpriteFromSheet(&hudNumberSprites[1], imageSheet, 194);
	C2D_SpriteFromSheet(&hudNumberSprites[2], imageSheet, 195);
	C2D_SpriteFromSheet(&hudNumberSprites[3], imageSheet, 196);
	C2D_SpriteFromSheet(&hudNumberSprites[4], imageSheet, 197);
	C2D_SpriteFromSheet(&hudNumberSprites[5], imageSheet, 198);
	C2D_SpriteFromSheet(&hudNumberSprites[6], imageSheet, 199);
	C2D_SpriteFromSheet(&hudNumberSprites[7], imageSheet, 200);
	C2D_SpriteFromSheet(&hudNumberSprites[8], imageSheet, 201);
	C2D_SpriteFromSheet(&hudNumberSprites[9], imageSheet, 202);
	C2D_SpriteFromSheet(&hudNumberSprites[10], imageSheet, 203);
	C2D_SpriteFromSheet(&hudNumberSprites[11], imageSheet, 204);
	C2D_SpriteFromSheet(&hudNumberSprites[12], imageSheet, 205);
	C2D_SpriteFromSheet(&hudNumberSprites[13], imageSheet, 206);
	C2D_SpriteFromSheet(&hudNumberSprites[14], imageSheet, 207);
	C2D_SpriteFromSheet(&hudNumberSprites[15], imageSheet, 208);
	C2D_SpriteFromSheet(&hudNumberSprites[16], imageSheet, 209);
	C2D_SpriteFromSheet(&hudNumberSprites[17], imageSheet, 210);
	C2D_SpriteFromSheet(&hudNumberSprites[18], imageSheet, 211);
	C2D_SpriteFromSheet(&hudNumberSprites[19], imageSheet, 212);
	C2D_SpriteFromSheet(&hudBaseSprite, imageSheet, 213);
	C2D_SpriteFromSheet(&hudBGSprite, imageSheet, 214);
	C2D_SpriteFromSheet(&hudLogoSprite, imageSheet, 215);
	C2D_SpriteFromSheet(&ppBaseSprite, imageSheet, 216);
	C2D_SpriteFromSheet(&ppArrowSprite, imageSheet, 217);
	C2D_SpriteFromSheet(&ppSprite, imageSheet, 218);

	C2D_SpriteFromSheet(&featherSprite, imageSheet, 219);

	C2D_SpriteFromSheet(&marioRacoonWalkSprites[0], imageSheet, 220);
	C2D_SpriteFromSheet(&marioRacoonWalkSprites[1], imageSheet, 221);
	C2D_SpriteFromSheet(&marioRacoonWalkSprites[2], imageSheet, 222);
	C2D_SpriteFromSheet(&marioRacoonWalkSprites[3], imageSheet, 223);
	C2D_SpriteFromSheet(&marioRacoonJumpSprite, imageSheet, 224);
	C2D_SpriteFromSheet(&marioRacoonFallSprites[0], imageSheet, 225);
	C2D_SpriteFromSheet(&marioRacoonFallSprites[1], imageSheet, 226);
	C2D_SpriteFromSheet(&marioRacoonFallSprites[2], imageSheet, 227);
	C2D_SpriteFromSheet(&marioRacoonSkidSprite, imageSheet, 228);
	C2D_SpriteFromSheet(&marioRacoonRunSprites[0], imageSheet, 229);
	C2D_SpriteFromSheet(&marioRacoonRunSprites[1], imageSheet, 230);
	C2D_SpriteFromSheet(&marioRacoonRunSprites[2], imageSheet, 231);
	C2D_SpriteFromSheet(&marioRacoonRunSprites[3], imageSheet, 232);
	C2D_SpriteFromSheet(&marioRacoonLeapSprites[0], imageSheet, 233);
	C2D_SpriteFromSheet(&marioRacoonLeapSprites[1], imageSheet, 234);
	C2D_SpriteFromSheet(&marioRacoonLeapSprites[2], imageSheet, 235);

	C2D_SpriteFromSheet(&marioSmallWalkCarrySprites[0], imageSheet, 236);
	C2D_SpriteFromSheet(&marioSmallWalkCarrySprites[1], imageSheet, 237);
	C2D_SpriteFromSheet(&marioSmallJumpCarrySprite, imageSheet, 238);
	C2D_SpriteFromSheet(&marioSmallKickSprite, imageSheet, 239);

	C2D_SpriteFromSheet(&marioBigDuckSprite, imageSheet, 240);
	C2D_SpriteFromSheet(&marioBigWalkCarrySprites[0], imageSheet, 241);
	C2D_SpriteFromSheet(&marioBigWalkCarrySprites[1], imageSheet, 242);
	C2D_SpriteFromSheet(&marioBigWalkCarrySprites[2], imageSheet, 243);
	C2D_SpriteFromSheet(&marioBigWalkCarrySprites[3], imageSheet, 244);
	C2D_SpriteFromSheet(&marioBigJumpCarrySprite, imageSheet, 245);
	C2D_SpriteFromSheet(&marioBigKickSprite, imageSheet, 246);

	C2D_SpriteFromSheet(&marioRacoonDuckSprite, imageSheet, 247);
	C2D_SpriteFromSheet(&marioRacoonWalkCarrySprites[0], imageSheet, 248);
	C2D_SpriteFromSheet(&marioRacoonWalkCarrySprites[1], imageSheet, 249);
	C2D_SpriteFromSheet(&marioRacoonWalkCarrySprites[2], imageSheet, 250);
	C2D_SpriteFromSheet(&marioRacoonWalkCarrySprites[3], imageSheet, 251);
	C2D_SpriteFromSheet(&marioRacoonJumpCarrySprite, imageSheet, 252);
	C2D_SpriteFromSheet(&marioRacoonKickSprite, imageSheet, 253);

	C2D_SpriteFromSheet(&brickBlockSprites[0], imageSheet, 254);
	C2D_SpriteFromSheet(&brickBlockSprites[1], imageSheet, 255);
	C2D_SpriteFromSheet(&brickBlockSprites[2], imageSheet, 256);
	C2D_SpriteFromSheet(&brickBlockSprites[3], imageSheet, 257);

	C2D_SpriteFromSheet(&marioSmallPipeSprite, imageSheet, 258);
	C2D_SpriteFromSheet(&marioBigPipeSprite, imageSheet, 259);
	C2D_SpriteFromSheet(&marioRacoonPipeSprite, imageSheet, 260);
	C2D_SpriteFromSheet(&marioRacoonSpinSprites[0], imageSheet, 261);
	C2D_SpriteFromSheet(&marioRacoonSpinSprites[1], imageSheet, 262);
	C2D_SpriteFromSheet(&marioRacoonSpinSprites[2], imageSheet, 263);
	C2D_SpriteFromSheet(&marioRacoonSpinSprites[3], imageSheet, 264);

	C2D_SpriteFromSheet(&lifeShroomSprite, imageSheet, 265);
}

#endif