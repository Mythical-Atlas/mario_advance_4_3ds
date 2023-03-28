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
    
    void destroy();

    void attachShader(GLenum type, const char* path);

    void link();

    void use();

    void bindTexture(class Texture* texture);
    void bindTexture(unsigned int texture);

    void uniform2fv(const char* name, vec2 vector);
    void uniformMatrix4fv(const char* name, mat4 matrix);
    void uniform4fv(const char* name, vec4 vector);
    void uniform1ui(const char* name, uint32_t integer);

    void useViewMatrix(class Camera* camera);
};

#endif