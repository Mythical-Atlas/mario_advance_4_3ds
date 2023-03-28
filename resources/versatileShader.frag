#version 430 core

in vec2 texCoords;

out vec4 color;

uniform vec4 colorMult;
uniform sampler2D image;
uniform vec2 frame;

void main(void) {
    color = texture(image, texCoords + frame) * colorMult;
}