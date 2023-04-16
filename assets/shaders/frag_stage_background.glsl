#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float layerOffset;

void main() {
    vec2 textureCoord = TexCoord;
    textureCoord.x += layerOffset;

    vec4 color = texture(ourTexture, textureCoord);

    FragColor = color;
}
