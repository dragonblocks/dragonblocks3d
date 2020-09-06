#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 ourTexCoord;
out vec4 cameraRelCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    cameraRelCoords = view  * model * vec4(aPos, 1.0);
    gl_Position = projection * cameraRelCoords;
    ourTexCoord = aTexCoord;
}
