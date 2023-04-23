#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float time = 0.0f;

float diamondPixelSize = 12.0f;
float progress = time;

vec2 iResolution = vec2(256, 160);

void transition() {
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    uv.x = 1.0 - uv.x;

    float xFraction = fract(gl_FragCoord.x / diamondPixelSize);
    float yFraction = fract(gl_FragCoord.y / diamondPixelSize);
    
    float xDistance = abs(xFraction - 0.5);
    float yDistance = abs(yFraction - 0.5);
    
    if (xDistance + yDistance + uv.x + uv.y > progress * 4.0f) {
        discard;
    }
}

void main() {
    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

    transition();

    FragColor = color;
}
