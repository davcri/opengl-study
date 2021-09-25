#version 330 core


in vec3 outCol;
in vec2 texCoord;

uniform sampler2D outTexture;
out vec4 FragColor;

void main() {
    FragColor = texture(outTexture, texCoord);
};