#version 330 core

in vec3 outCol;
in vec2 texCoord;

uniform sampler2D outTexture;
uniform sampler2D outTexture2;

out vec4 FragColor;

void main() {
    vec2 flipped_uv = texCoord;
    flipped_uv.y = 1.0 - flipped_uv.y;

    vec4 col1 = texture(outTexture, texCoord);
    vec4 col2 = texture(outTexture2, flipped_uv);
    
    if (col2.a == 0.0) {
        FragColor = col1;
    } else {
        FragColor = mix(col1, col2, 0.5);;
    }
};