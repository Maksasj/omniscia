#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
//uniform float tmp_uniform;

void main() {
    vec4 color = texture(ourTexture, TexCoord);
    color.w = 0.5;
    //color.x *= 0.8;

    FragColor = color;
}
