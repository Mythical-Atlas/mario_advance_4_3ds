#ifndef COLLISION_H
#define COLLISION_H

#include "mapsHandler.h"

typedef struct {
	float x;
	float y;
	float w;
	float h;
} BoundBox;

bool checkSolid(int t) {
	return t ==  59 ||
		   t ==  60 ||
		   t ==  61 ||
		   t ==  62 ||
		   t ==  80 ||
		   t ==  81 ||
		   t ==  82 ||
		   t ==  83 ||
		   t == 108 ||
		   t == 133 ||
		   t == 135 ||
		   t == 136 ||
		   t == 137 ||
		   t == 154 ||
		   t == 155 ||
		   t == 156 ||
		   t == 157 ||
		   t == 158 ||
		   t == 171 ||
		   t == 177 ||
		   t == 178 ||
		   t == 179 ||
		   t == 180 ||
		   t == 181 ||
		   t == 198 ||
		   t == 199 ||
		   t == 200 ||
		   t == 201 ||
		   t == 202 ||
		   t == 219 ||
		   t == 220 ||
		   t == 221;
}
bool checkPlatform(int t) {
	return t ==   9 ||
		   t ==  10 ||
		   t ==  11 ||
		   t ==  13 ||
		   t ==  14 ||
		   t ==  15 ||
		   t ==  72 ||
		   t ==  73 ||
		   t ==  74 ||
		   t ==  76 ||
		   t ==  77 ||
		   t ==  78;
}

BoundBox getBB(float x, float y, float w, float h) {
	BoundBox output;
	output.x = x;
	output.y = y;
	output.w = w;
	output.h = h;
	
	return output;
}

BoundBox getTileBB(int tx, int ty) {
	BoundBox output;
	output.x = tx * 16;
	output.y = ty * 16;
	output.w = 16;
	output.h = 16;
	
	return output;
}

bool checkBBOverlap(BoundBox b1, BoundBox b2) {
	bool xAxisOverlap = 0;
	bool yAxisOverlap = 0;
	
	if(b1.x >= b2.x && b1.x < b2.x + b2.w) {xAxisOverlap = 1;}
	if(b2.x >= b1.x && b2.x < b1.x + b1.w) {xAxisOverlap = 1;}
	
	if(b1.y >= b2.y && b1.y < b2.y + b2.h) {yAxisOverlap = 1;}
	if(b2.y >= b1.y && b2.y < b1.y + b1.h) {yAxisOverlap = 1;}
	
	return xAxisOverlap && yAxisOverlap;
}

int checkSurroundingSolids(int x, int y, Tilemap tilemap, int w, int h) {
	int ss = 0;
	
	for(int ix = -1; ix < 2; ix++) {
		for(int iy = -1; iy < 2; iy++) {
			if(x + ix >= 0 && x + ix < w && y + iy >= 0 && y + iy < h) {
				if(checkSolid(getMapValue(tilemap, x + ix, y + iy))) {
					if(ix == -1 && iy == -1) {ss += 0b00000001;}
					if(ix ==  0 && iy == -1) {ss += 0b00000010;}
					if(ix ==  1 && iy == -1) {ss += 0b00000100;}
					if(ix == -1 && iy ==  0) {ss += 0b00001000;}
					if(ix ==  1 && iy ==  0) {ss += 0b00010000;}
					if(ix == -1 && iy ==  1) {ss += 0b00100000;}
					if(ix ==  0 && iy ==  1) {ss += 0b01000000;}
					if(ix ==  1 && iy ==  1) {ss += 0b10000000;}
				}
			}
		}
	}
	
	return ss;
}

int checkSurroundingPlatforms(int x, int y, Tilemap tilemap, int w, int h) {
	int ss = 0;
	
	for(int ix = -1; ix < 2; ix++) {
		for(int iy = -1; iy < 2; iy++) {
			if(x + ix >= 0 && x + ix < w && y + iy >= 0 && y + iy < h) {
				if(checkPlatform(getMapValue(tilemap, x + ix, y + iy)) && y + iy >= y && iy != -1 && !(ix != 0 && ix == 0)) {
					if(ix == -1 && iy == -1) {ss += 0b00000001;}
					if(ix ==  0 && iy == -1) {ss += 0b00000010;}
					if(ix ==  1 && iy == -1) {ss += 0b00000100;}
					if(ix == -1 && iy ==  0) {ss += 0b00001000;}
					if(ix ==  1 && iy ==  0) {ss += 0b00010000;}
					if(ix == -1 && iy ==  1) {ss += 0b00100000;}
					if(ix ==  0 && iy ==  1) {ss += 0b01000000;}
					if(ix ==  1 && iy ==  1) {ss += 0b10000000;}
				}
			}
		}
	}
	
	return ss;
}

bool testOverlap(int xWidthMod, int yWidthMod, BoundBox b1, BoundBox b2) {
	BoundBox tb;
	tb.x = b2.x + b2.w * xWidthMod;
	tb.y = b2.y + b2.h * yWidthMod;
	tb.w = b2.w;
	tb.h = b2.h;
	
	return checkBBOverlap(b1, tb);
}

Vec2 findSmallestOverlap(BoundBox b1, BoundBox b2, int surroundingSolids, Vec2 vel, bool platform) {
	Vec2 output;
	output.x = 0;
	output.y = 0;
	if(!checkBBOverlap(b1, b2)) {return output;}
	
	float left  = (b1.x + b1.w) - b2.x;
	float right = b1.x - (b2.x + b2.w);
	float up    = (b1.y + b1.h) - b2.y;
	float down  = b1.y - (b2.y + b2.h);
	
	char allowDirections = 0b1111; // down up right left
	
	if(vel.x < 0) {allowDirections &= 0b1110;} // moving left, disallow move left
	if(vel.x > 0) {allowDirections &= 0b1101;} // moving right, disallow move right
	if(vel.y < 0) {allowDirections &= 0b1011;} // moving up, disallow move up
	if(vel.y > 0) {allowDirections &= 0b0111;} // moving down, disallow move down
	
	if(testOverlap(-1, -1, b1, b2) && (surroundingSolids &   1) ==   1) {allowDirections &= 0b1010;} // disallow up left
	if(testOverlap( 0, -1, b1, b2) && (surroundingSolids &   2) ==   2) {allowDirections &= 0b1011;} // disallow up
	if(testOverlap( 1, -1, b1, b2) && (surroundingSolids &   4) ==   4) {allowDirections &= 0b1001;} // disallow up right
	
	if(testOverlap(-1,  0, b1, b2) && (surroundingSolids &   8) ==   8) {allowDirections &= 0b1110;} // disallow left
	// middle
	if(testOverlap( 1,  0, b1, b2) && (surroundingSolids &  16) ==  16) {allowDirections &= 0b1101;} // disallow right
	
	if(testOverlap(-1,  1, b1, b2) && (surroundingSolids &  32) ==  32) {allowDirections &= 0b0110;} // disallow down left
	if(testOverlap( 0,  1, b1, b2) && (surroundingSolids &  64) ==  64) {allowDirections &= 0b0111;} // disallow down
	if(testOverlap( 1,  1, b1, b2) && (surroundingSolids & 128) == 128) {allowDirections &= 0b0101;} // disallow down right
	
	if(platform) {allowDirections &= 0b0100;}
	
	if(                                  fabs(left) <= fabs(right) && fabs(left)  <= fabs(up) && fabs(left)  <= fabs(down) && (allowDirections & 1) == 1) {output.x = left;}
	else if(fabs(right) <= fabs(left) &&                              fabs(right) <= fabs(up) && fabs(right) <= fabs(down) && (allowDirections & 2) == 2) {output.x = right;}
	else if(fabs(up)    <= fabs(left) && fabs(up)   <= fabs(right) &&                            fabs(up)    <= fabs(down) && (allowDirections & 4) == 4) {output.y = up;}
	else if(fabs(down)  <= fabs(left) && fabs(down) <= fabs(right) && fabs(down)  <= fabs(up)                              && (allowDirections & 8) == 8) {output.y = down;}
	
	return output;
}

#endif