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
	unsigned int pointer;

	void load(string path);
	void unload();
};

class Sprite {
public:
	Texture* texture;
	int uv[4];
	int vboIndex;
	vec2 pos;
	vec2 scale;
	float rotation;

    mat4 getModelMatrix();

	void init(Texture* texture, int vboIndex, int uv0, int uv1, int uv2, int uv3, int pos0, int pos1);
	void init(Texture* texture, int vboIndex, int uv0, int uv1, int uv2, int uv3);
	void init(Texture* texture, int vboIndex);

	void getData(float* buffer);

	void render(class RenderProgram* renderProgram, class RenderBuffer* renderBuffer, int xFrame, int yFrame);
	void render(class RenderProgram* renderProgram, class RenderBuffer* renderBuffer);
};

class Background {};

class HUD {};

#endif