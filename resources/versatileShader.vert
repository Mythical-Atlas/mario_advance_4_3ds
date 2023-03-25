#version 430 core

layout(location = 0) in vec3 screenPos;
layout(location = 1) in vec2 uvPos;
layout(location = 2) in vec4 color;

out vec2 texCoords;
out vec4 vertColor;

uniform mat4 viewMat;
uniform mat4 modelMat;

void main(void) {
    texCoords = uvPos;
    vertColor = color;
    gl_Position = viewMat * modelMat * vec4(screenPos, 1);
}