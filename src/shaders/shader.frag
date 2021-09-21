#version 330 core

out vec4 FragColor;

in vec3 outCol;

void main() {
    FragColor = vec4(outCol, 1.0);
};