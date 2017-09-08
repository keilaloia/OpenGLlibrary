#version 450
out vec4 outColor;
in vec2 vUV;

layout(location = 0) uniform sampler2D gdiffuse;
layout(location = 1) uniform sampler2D Idiffuse;
void main ()
{
	outColor = texture(gdiffuse, vUV.xy) * texture(Idiffuse, vUV.xy);
}