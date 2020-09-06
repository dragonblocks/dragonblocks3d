#version 330 core

in vec2 ourTexCoord;
in vec4 cameraRelCoords;

out vec4 finalColor;

uniform sampler2D ourTexture;
uniform vec3 sky;

void main()
{
    float texMultiplier = 750;
    float skyMultiplier = length(cameraRelCoords);
	finalColor = (texture(ourTexture, ourTexCoord) * texMultiplier + vec4(sky, 1.0) * skyMultiplier) / (texMultiplier + skyMultiplier);
}
