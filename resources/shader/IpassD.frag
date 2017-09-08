#version 450

in vec2 vUV;

// cam's view is important!
layout(location = 1) uniform mat4 view;

layout(location = 3) uniform mat4 lightView;
	
layout(location = 4) uniform vec4 lightColor;
layout(location = 5) uniform float intensity;


layout(location = 6) uniform sampler2D normalMap;

layout(location = 0) out vec4 outDiffuse;

void main()
{
	vec3 L = (view * -lightView[2]).xyz;
	vec3 N = texture(normalMap, vUV).xyz;

	float lamb = max(0, dot(-L, N));

	outDiffuse = lightColor * intensity * lamb;
}