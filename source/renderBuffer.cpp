#include "renderBuffer.hpp"
#include <cstddef>

void RenderBuffer::allocate(int attribCount, int attribSizes[], int size, float data[]) {
    this->size = size;

    glCreateBuffers(1, &glbuffer);
    glNamedBufferStorage(glbuffer, sizeof(GLfloat) * size, data, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);

    int totalSize = 0;
    for(int i = 0; i < attribCount; i++) {totalSize += attribSizes[i];}

    glCreateVertexArrays(1, &glarray);
    glVertexArrayVertexBuffer(glarray, 0, glbuffer, 0, sizeof(GLfloat) * totalSize);

    int offset = 0;
    for(int i = 0; i < attribCount; i++) {
        glEnableVertexArrayAttrib(glarray, i);
        glVertexArrayAttribFormat(glarray, i, attribSizes[i], GL_FLOAT, GL_FALSE, offset);
        glVertexArrayAttribBinding(glarray, i, 0);

        offset += sizeof(GLfloat) * attribSizes[i];
    }
}

RenderBuffer::RenderBuffer(int attribCount, int attribSizes[], int size) {allocate(attribCount, attribSizes, size, NULL);}
RenderBuffer::RenderBuffer(int attribCount, int attribSizes[], int size, float data[]) {allocate(attribCount, attribSizes, size, data);}

void RenderBuffer::destroy() {
    glDeleteBuffers(1, &glbuffer);
    glDeleteVertexArrays(1, &glarray);
}

void RenderBuffer::uploadData(int offset, int size, float data[]) {glNamedBufferSubData(glbuffer, sizeof(GLfloat) * offset, sizeof(GLfloat) * size, data);}

void RenderBuffer::bind() {
    glBindVertexArray(glarray);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void RenderBuffer::render(int offset, int size) {glDrawArrays(GL_TRIANGLE_STRIP, offset, size);}