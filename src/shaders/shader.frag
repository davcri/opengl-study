#version 330 core

in vec3 outCol;
in vec2 texCoord;

uniform sampler2D outTexture;
uniform sampler2D outTexture2;

out vec4 FragColor;

uniform float elapsed;
uniform float mixAmount;

void main() {
    float factor = sin(elapsed) + 1.0 / 2.0;
    // vec2 custom_uv = texCoord / max((1.0 + factor * 0.5), 0.25);

    vec4 col1 = texture(outTexture, texCoord);
    vec4 col2 = texture(outTexture2, texCoord);
    
    if (col2.a == 0.0) {
        FragColor = col1;
    } else {
        FragColor = mix(col1, col2, mixAmount);
    }
};