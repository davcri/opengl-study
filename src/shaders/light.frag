#version 330 core

vec3 lightCol = vec3(1.0, 1.0, 1.0);

out vec4 FragColor;

void main() {
    FragColor = vec4(lightCol, 1.0);
};