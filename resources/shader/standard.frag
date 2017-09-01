#version 450
//final output
out vec4 outColor;

//input from frag shader
in vec2 vUV;
in vec4 vPos;
in mat4 vTBN;

//camera
layout(location = 1) uniform mat4 view;

//surface Material Data
layout(location = 3) uniform sampler2D diffuseMap;
layout(location = 4) uniform sampler2D specularMap;
layout(location = 5) uniform sampler2D normalMap;
layout(location = 6) uniform float     glossMap;

//Light Data
layout(location = 7) uniform vec3 l_Dir;
layout(location = 8) uniform vec4 l_Color;
layout(location = 9) uniform float l_intensity;
layout(location = 10)uniform vec4 l_ambient;
layout(location = 11)uniform int l_type; // 0= dir, 1= pnt

//output variable// 4 targets, 3 color, and 1 float
layout(location = 0) out vec4 outFinal;
layout(location = 1) out vec4 outDiffuse;
layout(location = 2) out vec4 outSpecular;
layout(location = 3) out vec4 outNormal;



//illumination model terms
float calc_lambert(vec3 N, vec3 L);

//PHONG
float calc_phong(in vec3 N, in vec3 L, in vec3 V, in float power);
//AMBIENT
//ATTENUATION



void main()
{
	//read surface data
	vec3 normal  = (vTBN*(2*texture(normalMap, vUV) -1)).xyz;
	vec4 diffuse = texture(diffuseMap, vUV);
	vec4 specular = texture(specularMap, vUV);

	//split view comparison, remove later
	if(vPos.x < 0) normal = vTBN[2].xyz;

	//calculate light direction
	vec3 lDir = l_Dir;
	float attenuation = 1;
	if(l_type == 1)
	{
		lDir = normalize(vPos.xyz - l_Dir);
		attenuation = 1.0/distance(vPos.xyz, l_Dir);
	}
	
	//calculate our lighting factor
	float lamb = calc_lambert(normal, lDir);
	float ambi = 1;
	float spec = calc_phong(normal, lDir, normalize(view[3].xyz - vPos.xyz), glossMap);
	//calculate color terms
	vec4 outAmbient = diffuse * ambi * l_ambient;
	outDiffuse = diffuse * lamb * l_Color * l_intensity * attenuation;
	outSpecular= specular * spec * l_Color * l_intensity;

	outNormal = vec4 (normal, 0);
	

	outFinal = outAmbient + outDiffuse + outSpecular;
	//outColor = outSpecular;
	//outColor = vec4(normal,1);// test if they work!

}


float calc_lambert(in vec3 N, in vec3 L)
{
	return max(0,dot(N,-L));
}

float calc_phong(in vec3 N, in vec3 L, in vec3 V, in float power)
{	
	if(dot(N, -L) <= 0) return 0;
	vec3 R = reflect(L,N);
	return pow(max(0,dot(V, -R)), power);
}

