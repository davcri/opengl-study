#version 330 core

uniform vec3 ambientLightCol;
uniform float ambientLightStrength;
// uniform float elapsed;

out vec4 FragColor;

void main() {
    vec3 ambientLight = ambientLightStrength * ambientLightCol;
    FragColor = vec4(ambientLight, 1.0);
};