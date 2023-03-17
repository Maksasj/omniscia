#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec2 spriteFrameOffset = vec2(0.0, 0.0);
uniform vec2 spriteFrameSize = vec2(1.0, 1.0);

void main() {
    vec2 texCoord = TexCoord;

    texCoord *= spriteFrameSize;
    texCoord += spriteFrameOffset;

    vec4 color = texture(ourTexture, texCoord);

    FragColor = color;
}
