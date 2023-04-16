#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec2 transform = vec2(0.0, 0.0);
uniform mat2x2 rotation;
uniform vec2 scale = vec2(1.0, 1.0);

uniform float cameraZoom = 1.0;
uniform vec3 cameraPosition;

uniform float screenAspect = 1.6;

void main() {
   vec4 pos = vec4(vec4(aPos, 1.0f));

   pos.xy *= scale;
   pos.xy -= cameraPosition.xy;
   pos.xy += transform.xy;
   pos.x /= screenAspect;
   pos.xy *= cameraZoom;

   gl_Position = pos;

   ourColor = aColor;
   TexCoord = aTexCoord;
}
