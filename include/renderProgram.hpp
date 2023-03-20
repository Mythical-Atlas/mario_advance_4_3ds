#ifndef RENDER_PROGRAM_H
#define RENDER_PROGRAM_H

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class RenderProgram {
    GLuint pointer;
public:
    RenderProgram() {}
    RenderProgram(const char* name);
    
    void attachShader(GLenum type, const char* path);

    void link();

    void use();

    void bindTexture(class Texture* texture);
    void bindTexture(unsigned int texture);

    void uniformMatrix4fv(const char* name, mat4 matrix);

    void useViewMatrix(class Camera* camera);
};

#endif