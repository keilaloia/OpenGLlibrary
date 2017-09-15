#version 450

layout (location = 3) uniform vec4 tint;

out vec4 outcolor;

void main()
{
	outcolor = tint;
}