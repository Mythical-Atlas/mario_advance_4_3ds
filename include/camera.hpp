#ifndef CAMERA_H
#define CAMERA_H

#include "renderProgram.hpp"

using namespace std;

class Camera {
    int viewWidth;
    int viewHeight;
public:
    Camera() {}
    Camera(int viewWidth, int viewHeight);

    void useViewMatrix(RenderProgram program);
};

#endif