#version 430 core

layout(location = 0) in vec2 size;
layout(location = 1) in vec2 uvPos;

out vec2 texCoords;

uniform uint layer;
uniform mat4 viewMat;
uniform mat4 modelMat;

void main(void) {
    texCoords = uvPos;
    gl_Position = viewMat * modelMat * vec4(size, layer, 1);
}