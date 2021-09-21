#version 330 core

out vec4 FragColor;
uniform vec4 col;
in vec2 vertexPos;
vec4 outCol;

void main() {
    outCol = vec4(col);
    outCol.r = max(0.3, vertexPos.x + 0.5);
    outCol.g = max(0.2, vertexPos.y + 0.5);
    outCol.b = max(0.2, vertexPos.x + 0.5);
    FragColor = outCol;
};