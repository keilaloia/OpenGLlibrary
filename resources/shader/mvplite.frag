#version 450

in vec2 vUV;

layout (location = 3) uniform sampler2D diffuse;

out vec4 outColor;

void main()
{
	outcolor = texture(diffuse, vUV);
}