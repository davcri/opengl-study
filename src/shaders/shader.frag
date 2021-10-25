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
uniform vec3 viewPos;

float specularStrength = 0.5;

void main() {
    vec3 n = normalize(Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diffuseAmount = max(dot(n, lightDir), 0.0);
    vec3 diffuse = lightCol * diffuseAmount;
    vec3 ambient = 0.05 * vec3(1.0, 1.0, 1.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, n);
    float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularAmount * lightCol;
    
    FragColor = vec4((ambient + diffuse + specular) * objCol, 1.0);
};