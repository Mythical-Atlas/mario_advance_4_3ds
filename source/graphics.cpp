#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "graphics.hpp"
#include "renderBuffer.hpp"
#include "renderProgram.hpp"

void Texture::load(string path) {
    data = stbi_load(path.c_str(), &size[0], &size[1], &channels, 0);
    if(data == NULL) {
        cout << "Could not load image file" << endl;
        abort();
    }

#ifndef USE_OPENGL_4_3
    glCreateTextures(GL_TEXTURE_2D, 1, &pointer);
    glTextureStorage2D(pointer, 1, GL_RGBA8, size[0], size[1]);
    glTextureSubImage2D(pointer, 0, 0, 0, size[0], size[1], GL_RGBA, GL_UNSIGNED_BYTE, data);
#else
    glGenTextures(1, &pointer);
    glBindTexture(GL_TEXTURE_2D, pointer);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size[0], size[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
#endif

    stbi_image_free(data);
}

mat4 Sprite::getModelMatrix() {
    mat4 modelMat(1);
    modelMat = glm::scale(modelMat, vec3(scale.x, scale.y, 1));
    modelMat = glm::translate(modelMat, vec3(pos.x, pos.y, 0));
    modelMat = glm::rotate(modelMat, rotation, vec3(0, 0, 1)); // currently rotates around top left corner

    return modelMat;
}

void Sprite::init(Texture* texture, int vboIndex, int uv[4], int pos[3]) {
    this->texture = texture;
    this->vboIndex = vboIndex;
    this->uv[0] = uv[0];
    this->uv[1] = uv[1];
    this->uv[2] = uv[2];
    this->uv[3] = uv[3];
    this->pos = vec2(pos[0], pos[1]);
    scale = vec2(1, 1);
    rotation = 0;
}
void Sprite::init(Texture* texture, int vboIndex, int uv[4]) {init(texture, vboIndex, uv, new int[2]{0, 0});}
void Sprite::init(Texture* texture, int vboIndex) {init(texture, vboIndex, new int[4]{0, 0, texture->size[0], texture->size[1]});}

float* Sprite::getData() {
    float tw = texture->size[0];
    float th = texture->size[1];
    float sw = uv[2] - uv[0];
    float sh = uv[3] - uv[1];
    float ux1 = uv[0] / tw;
    float uy1 = uv[1] / th;
    float ux2 = uv[2] / tw;
    float uy2 = uv[3] / th;

    return new float[16] {
        0,  0,  ux1, uy1,
        0,  sh, ux1, uy2,
        sw, 0,  ux2, uy1,
        sw, sh, ux2, uy2,
    };
}

void Sprite::render(RenderProgram* renderProgram, RenderBuffer* renderBuffer, int frame[2]) {
    float tw = texture->size[0];
    float th = texture->size[1];
    float sw = uv[2] - uv[0];
    float sh = uv[3] - uv[1];

    renderProgram->use();
    renderProgram->bindTexture(texture);
    renderProgram->uniformMatrix4fv("modelMat", getModelMatrix());
    renderProgram->uniform2fv("frame", vec2(frame[0] * sw / tw, frame[1] * sh / th));
    renderProgram->uniform4fv("colorMult", vec4(1, 1, 1, 1));
    renderProgram->uniform1ui("layer", 0);

    renderBuffer->bind();
    renderBuffer->render(vboIndex * 4, 4);
}
void Sprite::render(RenderProgram* renderProgram, RenderBuffer* renderBuffer) {
    int frame[2] = {0, 0};
    render(renderProgram, renderBuffer, frame);
}