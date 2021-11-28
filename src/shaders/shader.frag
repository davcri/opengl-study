#version 330 core

// struct Material {
//   sampler2D diffuseMap;
//   sampler2D specularMap;
//   sampler2D emissionMap;
//   float shininess;
// };

// struct DirLight {
//   vec3 direction;

//   vec3 ambient;
//   vec3 diffuse;
//   vec3 specular;
// };

// struct PointLight {
//   vec3 position;

//   float constant;
//   float linear;
//   float quadratic;

//   vec3 ambient;
//   vec3 diffuse;
//   vec3 specular;
// };

// struct Light {
//     vec3 position;
//     vec3 direction;

//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;

//     float constant;
//     float linear;
//     float quadratic;

//     float cutoff;
//     float outerCutoff;
// };

// in vec3 Normal;
// in vec3 FragPos;

// uniform Material material;
// uniform Light light;
// uniform DirLight dirLight;
// #define NR_POINT_LIGHTS 4  
// uniform PointLight pointLights[NR_POINT_LIGHTS];

// uniform float elapsed;
// uniform vec3 viewPos;

// vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
//     vec3 lightDir = normalize(-light.direction);
//     // diffuse shading
//     float diff = max(dot(normal, lightDir), 0.0);
//     // specular shading
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
//     vec3 ambient  = light.ambient * vec3(texture(material.diffuseMap, TexCoords));
//     vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoords));
//     vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoords));
//     return (ambient + diffuse + specular);
// }


// vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
// {
//     vec3 lightDir = normalize(light.position - fragPos);
//     // diffuse shading
//     float diff = max(dot(normal, lightDir), 0.0);
//     // specular shading
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     // attenuation
//     float distance = length(light.position - fragPos);
//     float attenuation = 1.0 / (light.constant + light.linear * distance + 
//   			     light.quadratic * (distance * distance));    
//     // combine results
//     vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, TexCoords));
//     vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoords));
//     vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoords));

//     ambient *= attenuation;
//     diffuse *= attenuation;
//     specular *= attenuation;
//     return (ambient + diffuse + specular);
// } 

// void main() {
//     vec3 n = normalize(Normal);
//     vec3 outCol = CalcDirLight(dirLight, n, viewPos);
//     for(int i = 0; i < NR_POINT_LIGHTS; i++) {
//       outCol += CalcPointLight(pointLights[i], n, FragPos, viewPos);
//     }
//     FragColor = vec4(outCol, 1.0);
// };

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}