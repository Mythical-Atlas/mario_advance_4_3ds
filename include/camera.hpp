#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "renderProgram.hpp"

using namespace std;
using namespace glm;

class Camera {
public:
    int viewSize[2];
    vec2 pos;
	vec2 scale;
	float rotation;

    void init(int width, int height);
    mat4 getViewMatrix();
};

#endif