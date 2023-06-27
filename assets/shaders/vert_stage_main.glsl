#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

#define UNIFORM_INSTANCING_DATA_SIZE 1000
uniform int isInstancing = 0;

struct InstancingDataInstance {
   vec2 _position;
   vec2 _scale;
   vec2 _frameSize;
   vec2 _frameOffset;
};

layout (std140) uniform InstancingData {
   InstancingDataInstance instancingDataInsntance[UNIFORM_INSTANCING_DATA_SIZE];
};

out vec3 ourColor;
out vec2 TexCoord;
out vec2 textureFrameSize;
out vec2 textureFrameOffset;

uniform vec2 transform = vec2(0.0, 0.0);
uniform mat2x2 rotation;
uniform vec2 scale = vec2(1.0, 1.0);

// uniform float cameraZoom = 1.0;
uniform vec3 cameraPosition;

uniform vec2 spriteFrameSize = vec2(1.0, 1.0);
uniform vec2 spriteFrameOffset = vec2(0.0, 0.0);

uniform vec2 texturePixelSize = vec2(1.0, 1.0);
uniform vec2 frameBufferSize = vec2(255.0, 144.0);

uniform bool textureFlipHorizontal = false;
uniform bool textureFlipVertical = false;
uniform float textureAspect = 1.0;

uniform float screenAspect = 1.6;

void main() {
   vec4 pos = vec4(aPos, 1.0f);

   float scaleFactorX = (texturePixelSize.x * spriteFrameSize.x) / (frameBufferSize.x);
   float scaleFactorY = (texturePixelSize.y * spriteFrameSize.y) / (frameBufferSize.y);

   pos.x *= scaleFactorX;
   pos.y *= scaleFactorY;

   vec2 pixelTransform = (transform.xy + vec2(0.5, 0.5) - cameraPosition.xy) * frameBufferSize;
   vec2 newTransform = vec2(trunc(pixelTransform.x), trunc(pixelTransform.y));
   newTransform /= frameBufferSize;
   newTransform -= vec2(0.5, 0.5);

   // pos.x *= textureAspect;
   // pos.x *= spriteFrameSize.x / spriteFrameSize.y;

   // pos.xy -= cameraPosition.xy;
   pos.xy += newTransform;
   // pos.x /= screenAspect;

   // textureFrameSize = spriteFrameSize;
   // textureFrameOffset = spriteFrameOffset;

   gl_Position = pos;

   ourColor = aColor;
   TexCoord = (aTexCoord * spriteFrameSize) + spriteFrameOffset;
   // TexCoord = aTexCoord;
}
