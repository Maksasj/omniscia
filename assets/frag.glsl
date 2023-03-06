#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float tmp_uniform;

void main() {
    vec4 color = texture(ourTexture, TexCoord);

    color.x = tmp_uniform;

    FragColor = color;
}
