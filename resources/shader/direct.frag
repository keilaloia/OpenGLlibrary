#version 450

layout(location = 3) uniform mat4 lproj;
layout(location = 4) uniform mat4 lview;
layout(location = 5) uniform sampler2D shadowmap;

in vec2 vUV;
in vec4 vPos;

uniform float shadowBias = 0.01;

// Simple matrix that converts from clip space (-1,1) to UV space (0,1)
uniform mat4 clipToUV = mat4(0.5f, 0.0f, 0.0f, 0.0f,
							 0.0f, 0.5f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.5f, 0.0f,
							 0.5f, 0.5f, 0.5f, 1.0f);

out vec4 outColor;

void main()
{

	vec4 sUV = clipToUV * lproj * lview * vPos;
	
	float visibility = 1;
	if(texture(shadowmap,sUV.xy).r  < sUV.z - shadowBias)
		visibility = 0;	

		
	outColor = vec4(1,1,0,1) * visibility;
}

float ghetto_pcf(in sampler2D shadowMap, in vec4 shadowPosition, int iterations)
{
	vec2 sDim = textureSize(shadowMap,0).xy;
	float retval = 0;
	
	vec2 uv = shadowPosition.xy;
	float z = shadowPosition.z - 0.01;

	//	if(texture(shadowmap,sUV.xy).r  < sUV.z - shadowBias)
	for(int i = -iterations; i <= iterations; ++i)
	{		
		if(!(texture(shadowMap, uv + vec2(i,0)/sDim).r < z))
			retval++;

		if(!(texture(shadowMap, uv + vec2(0,i)/sDim).r < z))
			retval++;
	}

	return retval / (iterations*4.0);
}