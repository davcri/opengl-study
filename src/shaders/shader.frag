#version 330 core

out vec4 FragColor;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform Light light;

uniform float elapsed;
uniform vec3 viewPos;

void main() {
    // diffuse
    vec3 n = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diffuseAmount = max(dot(n, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diffuseAmount * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, n);
    float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularAmount * material.specular;

    // ambient
    vec3 ambient = light.ambient * material.ambient;
    
    FragColor = vec4(ambient + diffuse + specular, 1.0);
};