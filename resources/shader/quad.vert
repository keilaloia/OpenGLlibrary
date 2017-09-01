#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;

out vec2 vUV;

vec4 crossblur(in sampler2D map, in vec2 UV, in int it);


void main()
{
	gl_Position = position;
	vUV = texCoord;
}
