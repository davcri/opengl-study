#version 330 core

out vec4 FragColor;

uniform float elapsed;

uniform vec3 objCol;
uniform vec3 ambientLightCol;
uniform float ambientLightStrength;

void main() {
    vec3 ambientLight = ambientLightStrength * ambientLightCol;
    FragColor = vec4(ambientLight * objCol, 1.0);
};