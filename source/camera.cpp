#include "renderProgram.hpp"
#include "camera.hpp"

//using namespace glm;

void Camera::init(int width, int height) {
    viewSize[0] = width;
    viewSize[1] = height;

    pos = vec2(0, 0);
    scale = vec2(1, 1);
    rotation = 0;
}

mat4 Camera::getViewMatrix() {
    mat4 viewMat(1);
    viewMat = glm::scale(viewMat, vec3(2.0f / viewSize[0] * scale.x, -2.0f / viewSize[1] * scale.y, 1));
    viewMat = glm::translate(viewMat, vec3(-viewSize[0] / 2.0f - pos.x, -viewSize[1] / 2.0f - pos.y, 0));
    viewMat = glm::rotate(viewMat, rotation, vec3(0, 0, 1)); // currently rotates around top left corner

    return viewMat;
}