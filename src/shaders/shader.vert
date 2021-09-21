#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

uniform vec2 pos;

out vec3 outCol;

void main() {
  gl_Position = vec4(aPos.x * pos.x, aPos.y * pos.y, aPos.z, 1.0);
  outCol = aCol;
};
