#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in vec2 textureFrameSize;
in vec2 textureFrameOffset;

uniform sampler2D ourTexture;

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

    texCoord *= textureFrameSize;
    texCoord += textureFrameOffset;

    vec4 color = texture(ourTexture, texCoord);

    FragColor = color;
}
