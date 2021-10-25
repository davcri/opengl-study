#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 objCol;
// lights
uniform vec3 lightCol;
uniform vec3 lightPos;
uniform float lightStrength;
uniform vec3 viewPos;

uniform float elapsed;

void main() {
  gl_Position = proj * view * model * vec4(aPos, 1.0);
  FragPos = vec3(model * vec4(aPos, 1.0));
  Normal = mat3(transpose(inverse(model))) * aNormal; // improvement: do this on CPU
};
