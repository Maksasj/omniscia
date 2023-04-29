#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float layerOffset;
uniform float transparency = 1.0f;

void main() {
    vec2 textureCoord = TexCoord;
    textureCoord.x += layerOffset;

    vec4 color = texture(ourTexture, textureCoord);
    color *= transparency;

    FragColor = color;
}
