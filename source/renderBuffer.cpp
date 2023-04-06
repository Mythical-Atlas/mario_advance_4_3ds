#include "renderBuffer.hpp"
#include <cstddef>

void RenderBuffer::allocate(int attribCount, int attribSizes[], int size, float data[]) {
    this->size = size;

    int totalSize = 0;
    for(int i = 0; i < attribCount; i++) {totalSize += attribSizes[i];}

#ifndef USE_OPENGL_4_3
    glCreateBuffers(1, &glbuffer);
    glNamedBufferStorage(glbuffer, sizeof(GLfloat) * size, data, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &glarray);
    glVertexArrayVertexBuffer(glarray, 0, glbuffer, 0, sizeof(GLfloat) * totalSize);

    int offset = 0;
    for(int i = 0; i < attribCount; i++) {
        glEnableVertexArrayAttrib(glarray, i);
        glVertexArrayAttribFormat(glarray, i, attribSizes[i], GL_FLOAT, GL_FALSE, offset);
        glVertexArrayAttribBinding(glarray, i, 0);

        offset += sizeof(GLfloat) * attribSizes[i];
    }
#else
    glGenBuffers(1, &glbuffer); // vbo
    glBindBuffer(GL_ARRAY_BUFFER, glbuffer);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &glarray); // vao
    glBindVertexArray(glarray);

    glBindVertexBuffer(0, glbuffer, 0, sizeof(GLfloat) * totalSize);

    int offset = 0;
    for(int i = 0; i < attribCount; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribFormat(i, attribSizes[i], GL_FLOAT, GL_FALSE, offset);
        glVertexAttribBinding(i, 0);

        offset += sizeof(GLfloat) * attribSizes[i];
    }
#endif
}

RenderBuffer::RenderBuffer(int attribCount, int attribSizes[], int size) {allocate(attribCount, attribSizes, size, NULL);}
RenderBuffer::RenderBuffer(int attribCount, int attribSizes[], int size, float data[]) {allocate(attribCount, attribSizes, size, data);}

void RenderBuffer::destroy() {
    glDeleteBuffers(1, &glbuffer);
    glDeleteVertexArrays(1, &glarray);
}

void RenderBuffer::uploadData(int offset, int size, float* data) {
#ifndef USE_OPENGL_4_3
    glNamedBufferSubData(glbuffer, sizeof(GLfloat) * offset, sizeof(GLfloat) * size, data);
#else
    glBindBuffer(GL_ARRAY_BUFFER, glbuffer);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * offset, sizeof(GLfloat) * size, data);
#endif
}

void RenderBuffer::bind() {
    glBindVertexArray(glarray);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void RenderBuffer::render(int offset, int size) {glDrawArrays(GL_TRIANGLE_STRIP, offset, size);}