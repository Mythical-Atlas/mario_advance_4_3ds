#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Shape {};

class Texture {
public:
	int size[2];
	int channels;
	unsigned char* data; // needed?
	unsigned int pointer;

	void load(string path);
};

class Sprite {
public:
	Texture* texture;
	vec2 uv[2];
	vec2 pos;
	vec2 scale;
	float rotation;

    mat4 getModelMatrix();

	void init(Texture* texture, vec2 uv[2], vec2 pos, vec2 scale, float rotation);
	void init(Texture* texture, int uv[4], int pos[2]);
	void init(Texture* texture, vec2 uv[2]);
	void init(Texture* texture);

	float* getData();

	void render(class RenderProgram* renderProgram, class RenderBuffer* renderBuffer, int off, int size);
};

class Background {};

class Animation {};

class HUD {};

#endif