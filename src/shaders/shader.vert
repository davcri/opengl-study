#version 330 core

layout(location = 0) in vec3 aPos;

uniform vec2 pos;
out vec2 vertexPos;

void main() {
  gl_Position = vec4(aPos.x * pos.x, aPos.y * pos.y, aPos.z, 1.0);
  vertexPos = vec2(gl_Position);
};
