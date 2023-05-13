#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float transparency = 1.0f;

uniform float transitionCircleProgress = 0.0f;
uniform float transitionChapterCircleProgress = 0.0f;

uniform float transitionSideProgress = 0.0f;
uniform float transitionSideDiamondPixelSize = 12.0f;

uniform float letterBoxUpperBound = 0.0f;
uniform float letterBoxLowerBound = 0.0f;

uniform float bottomShadow = 0.3;

uniform float shadowTintStrength = 0.0f;

vec2 gameResolution = vec2(256, 144);

vec4 transition_side(vec2 uv, vec4 color) {
    uv.x = 1.0 - uv.x;

    float xFraction = fract(gl_FragCoord.x / transitionSideDiamondPixelSize);
    float yFraction = fract(gl_FragCoord.y / transitionSideDiamondPixelSize);
    
    float xDistance = abs(xFraction - 0.5);
    float yDistance = abs(yFraction - 0.5);
    
    if (xDistance + yDistance + uv.x + uv.y < transitionSideProgress * 4.0f) {
        color.w = 1.0;
    }

    return color;
}

vec4 transition_circle(vec2 uv, vec4 color) {
    uv -= vec2(0.5, 0.5);
    uv.x *= gameResolution.x / gameResolution.y;

    float additionalLength = sin(uv.x * 50.0) + sin(uv.y * 50.0);
    additionalLength *= 0.012; 

    if(length(uv) + additionalLength < transitionCircleProgress) {
        color.w = 1.0;
    }

    return color;
}

vec4 transition_chapter_circle(vec2 uv, vec4 color) {
    uv -= vec2(0.5, 0.5);
    uv.x *= gameResolution.x / gameResolution.y;

    float additionalLength = sin(uv.x * 50.0) + sin(uv.y * 50.0);
    additionalLength *= 0.012; 

    if(length(uv) + additionalLength > (1.1 - transitionChapterCircleProgress)) {
        color = vec4(1.0, 1.0, 1.0, 1.0);
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

vec4 bottom_shadow(vec2 uv, vec4 color) {
    if(uv.y < bottomShadow) {
        float upperShadow = 1.0 - bottomShadow;
        float value = uv.y + upperShadow;

        color.w = 1.0 - value * value * value;
    }

    return color;
}

vec4 color_overlay(vec2 uv, vec4 color) {
    color.w = shadowTintStrength;
    return color;
}

void main() {
    vec2 uv = gl_FragCoord.xy / gameResolution.xy;
    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

    color = bottom_shadow(uv, color);
    color = color_overlay(uv, color);
    color = transition_side(uv, color);
    color = transition_circle(uv, color);
    color = transition_chapter_circle(uv, color);
    color = letter_box(uv, color);

    color *= transparency;

    FragColor = color;
}
