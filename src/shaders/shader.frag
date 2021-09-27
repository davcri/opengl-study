#version 330 core

in vec3 outCol;
in vec2 texCoord;

uniform sampler2D outTexture;
uniform sampler2D outTexture2;

out vec4 FragColor;

uniform float elapsed;
uniform float w;
uniform float h;

void main() {
    float factor = sin(elapsed) + 1.0 / 2.0;
    float textureSize = max(w, h);
    vec2 custom_uv = texCoord / max((1.0 + factor * textureSize * 0.5), 0.25);

    vec4 col1 = texture(outTexture, custom_uv);
    FragColor = col1;
    // vec4 col2 = texture(outTexture2, custom_uv);
    
    // if (col2.a == 0.0) {
    //     FragColor = col1;
    // } else {
    //     FragColor = mix(col1, col2, 0.5);
    // }
};