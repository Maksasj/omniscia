#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float time;

void main() {
    vec4 color = texture(ourTexture, TexCoord);

    FragColor = color;
}