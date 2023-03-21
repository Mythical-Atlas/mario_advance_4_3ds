#version 430 core

layout(location = 0) in vec4 coord;

out vec2 texCoords;

uniform mat4 viewMat;
uniform mat4 modelMat;

void main(void) {
    texCoords = coord.zw;
    gl_Position = (/*projection * */viewMat * modelMat) * vec4(coord.xy, 0.0, 1.0);
}