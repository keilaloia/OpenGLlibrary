#version 450

out vec4 outColor;

in vec2 vUV;
in vec3 vPos;
in vec3 vNormal;

layout(location = 3) uniform sampler2D map;

layout(location = 4) uniform vec3 LP;
layout(location = 5) uniform vec4 lightColor;
layout(location = 6) uniform float lightIntensity = 4.0f;

void main()
{
	vec4 surfaceColor = texture(map, vUV);
	vec3 DISP = vPos - LP;

	float d = length(DISP);// distance(vPos, LP);
	float attenuation = 1.0/(d);
	vec3  L = normalize(DISP);
	vec3  N = vNormal;

	float lambFactor = max(0,dot(N, -L));

	vec4 lambTerm = surfaceColor * lambFactor *
					lightColor 
					* lightIntensity * attenuation;

	outColor = lambTerm;

}