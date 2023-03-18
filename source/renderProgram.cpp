#include <string>
#include <fstream>

#include "renderProgram.hpp"

using namespace std;

RenderProgram::RenderProgram(const char* name) {
    pointer = glCreateProgram();
    glObjectLabel(GL_PROGRAM, pointer, -1, name);
}

void RenderProgram::attachShader(GLenum type, const char* path) {
    string data;
    string line = "";
    ifstream fileStream(path, ios::in);

    if(!fileStream.is_open()) {
        fprintf(stderr, "Could not load shader file\n");
        abort();
    }

    while(!fileStream.eof()) {
        getline(fileStream, line);
        data.append(line + "\n");
    }

    fileStream.close();
    const char *source = data.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint shader_ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if(!shader_ok) {
        fprintf(stderr, "Failed to compile shader");
        abort();
    }

    glAttachShader(pointer, shader);
    glDeleteShader(shader);
}

void RenderProgram::link() {
    glLinkProgram(pointer);
    GLint result;
    glGetProgramiv(pointer, GL_LINK_STATUS, &result);
    if(result != GL_TRUE) {
        char msg[10240];
        glGetProgramInfoLog(pointer, 10240, NULL, msg);
        fprintf(stderr, "Linking program failed:\n%s\n", msg);
        abort();
    }
}

void RenderProgram::use() {glUseProgram(pointer);}

void RenderProgram::bindTexture(Texture texture) {
    glBindTexture(GL_TEXTURE_2D, texture.pointer);
    glProgramUniform1i(pointer, 0, 0);
}
void RenderProgram::bindTexture(unsigned int texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glProgramUniform1i(pointer, 0, 0);
}

void RenderProgram::uniformMatrix4fv(const char* name, glm::mat4 matrix) {
    glUniformMatrix4fv(glGetUniformLocation(pointer, "viewMat"), 1, GL_FALSE, glm::value_ptr(matrix));
}