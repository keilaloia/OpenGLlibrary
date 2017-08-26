#version 450

layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texcoord;

layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 1) uniform mat4 model;

out vec2 vUV;

void main()
{
	gl_Position = proj * view * model * position;
	vUV = texcoord;
}