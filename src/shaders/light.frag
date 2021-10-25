#version 330 core

uniform vec3 lightCol;
uniform float lightStrength;

out vec4 FragColor;

void main() {
    vec3 light = lightStrength * lightCol;
    FragColor = vec4(light, 1.0);
};