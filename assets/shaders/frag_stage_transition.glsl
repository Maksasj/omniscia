#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float transitionProgress = 0.0f;
uniform float transitionDiamondPixelSize = 12.0f;

uniform float letterBoxUpperBound = 0.0f;
uniform float letterBoxLowerBound = 0.0f;

vec2 gameResolution = vec2(256, 160);

vec4 transition(vec2 uv, vec4 color) {
    uv.x = 1.0 - uv.x;

    float xFraction = fract(gl_FragCoord.x / transitionDiamondPixelSize);
    float yFraction = fract(gl_FragCoord.y / transitionDiamondPixelSize);
    
    float xDistance = abs(xFraction - 0.5);
    float yDistance = abs(yFraction - 0.5);
    
    if (xDistance + yDistance + uv.x + uv.y < transitionProgress * 4.0f) {
        color.w = 1.0;
    }

    return color;
}

vec4 letter_box(vec2 uv, vec4 color) {
    if(uv.y < letterBoxLowerBound) {
        color.w = 1.0;
    }
    
    if(uv.y > 1.0 - letterBoxUpperBound) {
        color.w = 1.0;
    }

    return color;
}

void main() {
    vec2 uv = gl_FragCoord.xy / gameResolution.xy;
    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

    color = transition(uv, color);
    color = letter_box(uv, color);

    FragColor = color;
}
