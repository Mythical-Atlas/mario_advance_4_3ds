#version 460 core

layout(location = 0) in vec4 coord;

out vec2 texCoords;

uniform mat4 viewMat;

void main(void) {
    texCoords = coord.zw;
    gl_Position = viewMat * vec4(coord.xy, 0.0, 1.0);
}