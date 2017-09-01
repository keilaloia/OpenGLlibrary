#version 450
//vertex attributes
layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in vec4 normal;
layout(location = 4) in vec4 tangent;
layout(location = 5) in vec4 bitangent;


//camera
layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;

//model
layout(location = 2) uniform mat4 model;

out vec2 vUV;
out vec4 vPos;
out mat4 vTBN;

out vec4 vTEST;

void main()
{
	gl_Position = proj * view * model * position;

	vTBN = model * mat4(tangent, bitangent, normal, vec4(0,0,0,0));

	vPos = model * position;
	vUV = texcoord;

	//vTEST = vec4(texcoord,0,1);
	//vTBN = model * mat4(tangent, bitangent, normal, vec4(0,0,0,1));
}