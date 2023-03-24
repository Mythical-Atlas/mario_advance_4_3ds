#version 460 core

in vec3 vertColor;

out vec4 color;

void main(void) {
    color = vec4(vertColor, 1.0);
}