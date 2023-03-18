#ifndef RENDER_BUFFER_H
#define RENDER_BUFFER_H

#include <glad/glad.h>

class RenderBuffer {
    GLuint glbuffer;
    GLuint glarray;
    int size;

    void allocate(int attribCount, int attribSizes[], int size, float data[]);
public:
    RenderBuffer() {}
    RenderBuffer(int attribCount, int attribSizes[], int size);
    RenderBuffer(int attribCount, int attribSizes[], int size, float data[]);

    void uploadData(int offset, int size, float data[]);

    void destroy();

    void bind();

    void draw(int offset, int size);
};

#endif