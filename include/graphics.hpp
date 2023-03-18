#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <iostream>

#include <glad/glad.h>

using namespace std;

class Shape {};

class Texture {
public:
	int size[2];
	int channels;
	unsigned char* data; // needed?
	unsigned int pointer;

	void load(string path);
};

class Sprite {};

class Background {};

class Animation {};

//class Camera {
	// position
//};

class HUD {};

/*
namespace cgrph {

}
*/

#endif