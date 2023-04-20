#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
//uniform float tmp_uniform;

void main() {
    vec4 color = texture(ourTexture, TexCoord);

    if(TexCoord.y < 0.3) {
        color.xyz *= (TexCoord.y + 0.7) * (TexCoord.y + 0.7);
    }

    FragColor = color;
}
