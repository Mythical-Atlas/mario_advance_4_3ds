#version 430 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D image;

void main(void) {
    color = texture(image, texCoords);
}