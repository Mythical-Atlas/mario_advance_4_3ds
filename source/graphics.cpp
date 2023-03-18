#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "graphics.hpp"

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