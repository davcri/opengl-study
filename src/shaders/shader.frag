#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform float elapsed;
uniform vec3 objCol;
// lights
uniform vec3 lightCol;
uniform vec3 lightPos;
uniform float lightStrength;

void main() {
    vec3 n = normalize(Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diffuseAmount = max(dot(n, lightDir), 0.0);
    vec3 diffuse = lightCol * diffuseAmount;
    vec3 ambient = 0.05 * vec3(1.0, 1.0, 1.0);
    
    FragColor = vec4((ambient + diffuse) * objCol, 1.0);
};