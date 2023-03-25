#version 430 core

in vec2 texCoords;
in vec4 vertColor;

out vec4 color;

uniform sampler2D image;
uniform vec2 frame;

void main(void) {
    color = texture(image, texCoords * frame) * vertColor;
}