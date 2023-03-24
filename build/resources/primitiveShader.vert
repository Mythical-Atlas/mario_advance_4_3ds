#version 460 core

layout(location = 0) in vec2 coord;
layout(location = 1) in vec3 color;

out vec3 vertColor;

uniform mat4 viewMat;

void main(void) {
    gl_Position = viewMat * vec4(coord, 0.0, 1.0);
    vertColor = color;
}