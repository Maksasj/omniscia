#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec2 spriteFrameOffset = vec2(0.0, 0.0);
uniform vec2 spriteFrameSize = vec2(1.0, 1.0);
uniform float textureAspect = 1.0;

uniform bool textureFlipHorizontal = false;
uniform bool textureFlipVertical = false;

void main() {
    vec2 texCoord = TexCoord;

    if(textureFlipHorizontal) {
        texCoord.y = 1.0 - texCoord.y;
    }

    if(textureFlipVertical) {
        texCoord.x = 1.0 - texCoord.x;
    }

    texCoord *= spriteFrameSize;
    texCoord += spriteFrameOffset;

    vec4 color = texture(ourTexture, texCoord);

    FragColor = color;
}
