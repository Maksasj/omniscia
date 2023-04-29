#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float time;

uniform float transparency = 1.0f;

void main() {
    vec4 color = texture(ourTexture, TexCoord);
    color *= transparency;

    FragColor = color;
}
