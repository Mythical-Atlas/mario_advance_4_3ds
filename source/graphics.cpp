#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "graphics.hpp"
#include "renderBuffer.hpp"
#include "renderProgram.hpp"

void Texture::load(string path) {
    data = stbi_load(path.c_str(), &size[0], &size[1], &channels, 0);
    if(data == NULL) {
        cerr << "Could not load image file" << endl;
        abort();
    }
    
    glCreateTextures(GL_TEXTURE_2D, 1, &pointer);
    glTextureStorage2D(pointer, 1, GL_RGBA8, size[0], size[1]);
    glTextureSubImage2D(pointer, 0, 0, 0, size[0], size[1], GL_RGBA, GL_UNSIGNED_BYTE, data);
}

mat4 Sprite::getModelMatrix() {
    mat4 modelMat(1);
    modelMat = glm::scale(modelMat, vec3(scale.x, scale.y, 1));
    modelMat = glm::translate(modelMat, vec3(pos.x, pos.y, 0));
    modelMat = glm::rotate(modelMat, rotation, vec3(0, 0, 1)); // currently rotates around top left corner

    return modelMat;
}

void Sprite::init(Texture* texture, vec2 uv[2], vec2 pos, vec2 scale, float rotation) {
    this->texture = texture;
    this->uv[0] = uv[0];
    this->uv[1] = uv[1];
    this->pos = pos;
    this->scale = scale;
    this->rotation = rotation;
}
void Sprite::init(Texture* texture, vec2 uv[2]) {init(texture, uv, vec2(0, 0), vec2(1, 1), 0);}

void Sprite::render(RenderProgram* renderProgram, RenderBuffer* renderBuffer) {
    renderProgram->use();
    renderProgram->bindTexture(texture);
    renderProgram->uniformMatrix4fv("modelMat", getModelMatrix());

    renderBuffer->bind();
    renderBuffer->render(0, 4);
}