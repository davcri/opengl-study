#version 330 core

out vec4 FragColor;

uniform float elapsed;

uniform vec3 objCol;
uniform vec3 lightCol;

void main() {
    FragColor = vec4(lightCol * objCol, 1.0);
};