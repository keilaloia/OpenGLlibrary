#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;

out vec2 vUV;

layout(location = 1) uniform mat4 model;

void main()
{
	gl_Position = model * position;
	vUV = texCoord;
}