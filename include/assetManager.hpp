#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "audio.hpp"
#include "animation.hpp"
#include "graphics.hpp"

class AssetManager {
public:
	Texture* textures[5];
	Sprite* sprites[5];
	Animation* animations[5];

	// textures
	// sprites
	// animations
	// audioStreams
	// tilesets
	// tilemaps
	// objects

	// use define constants for max of things
	// use arrays of pointers, then dynamically allocate/deallocate when called
};

#endif