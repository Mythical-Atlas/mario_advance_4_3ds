#include <glm/gtc/matrix_transform.hpp>

#include "renderProgram.hpp"
#include "camera.hpp"

using namespace glm;

Camera::Camera(int viewWidth, int viewHeight) {
    this->viewWidth = viewWidth;
    this->viewHeight = viewHeight;
}

void Camera::useViewMatrix(RenderProgram program) {
    mat4 viewMat(1);
    viewMat = scale(viewMat, vec3(2.0f / viewWidth, -2.0f / viewHeight, 1));
    viewMat = translate(viewMat, vec3(-viewWidth / 2.0f, -viewHeight / 2.0f, 0));

    program.uniformMatrix4fv("viewMat", viewMat);
}