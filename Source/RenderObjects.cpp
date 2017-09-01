#define GLM_FORCE_SWIZZLE
#include "glinc.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include <iostream>

glm::vec4 calcTangent(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
	glm::vec4 p1 = v1.position - v0.position;
	glm::vec4 p2 = v2.position - v0.position;

	glm::vec2 t1 = v1.texCoord - v0.texCoord;
	glm::vec2 t2 = v2.texCoord - v0.texCoord;

	return glm::normalize((p1*t2.y - p2*t1.y) / (t1.x*t2.y - t1.y*t2.x));
	//UV.x will follow the tangents
	//UV.y will follow the bitangents
}

void solveTangents(Vertex *v, size_t vsize,
							 const unsigned *idx, size_t isize)
{
	for (int i = 0; i < isize; i += 3)
	{
		glm::vec4 T = calcTangent(v[idx[i]], v[idx[i + 1]], v[idx[i + 2]]);

		for (int j = 0; j < 3; ++j)
			v[idx[i + j]].tangent = glm::normalize(T + v[idx[i + j]].tangent);
	}
	
	for (int i = 0; i < vsize; ++i)
		v[i].bitangent = glm::vec4(glm::cross(v[i].normal.xyz(), v[i].tangent.xyz()), 0);
}

Geometry makeGeometry(const Vertex *vertices, size_t vsize,
	const unsigned *indices, size_t isize)
{
	Geometry retval = { 0, 0, 0, isize };

	//Declare our openGL objects and acquire handles
	glGenBuffers(1, &retval.vbo);
	glGenBuffers(1, &retval.ibo);
	glGenVertexArrays(1, &retval.handle);

	// now lets scope the variable!
	glBindVertexArray(retval.handle);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo);

	//initialize all of our buffers
	glBufferData(GL_ARRAY_BUFFER,
		vsize*sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		isize * sizeof(unsigned), indices, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);//position attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	
	glEnableVertexAttribArray(1);//color attribute 
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	
	glEnableVertexAttribArray(2); //texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	glEnableVertexAttribArray(3); //normal
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)40);

	glEnableVertexAttribArray(4); //tangent
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)56);

	glEnableVertexAttribArray(5); //bitangent
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)72);

	//unbind the variable
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	return retval;
}

void freeGeometry(Geometry &g)
{
	glDeleteBuffers(1, &g.vbo);
	glDeleteBuffers(1, &g.ibo);
	glDeleteVertexArrays(1, &g.handle);
	g = { 0,0,0,0 };

}

Shader makeShader(const char *vsource, const char *fsource)
{
	Shader retval = { 0 };

	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//load up the source code and compile
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);

	glCompileShader(vs);
	glCompileShader(fs);
	//write ifdef debug here
#ifdef _DEBUG
	GLint success = GL_FALSE;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(vs, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

	success = GL_FALSE;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(fs, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}
#endif _DEBUG



	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);

	glLinkProgram(retval.handle);

#ifdef _DEBUG
	success = GL_FALSE;
	glGetProgramiv(retval.handle, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetProgramInfoLog(retval.handle, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}
#endif _DEBUG

	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

//clean up shader program
void freeShader(Shader &s)
{
	glDeleteProgram(s.handle);
	s = { 0 };
}


Texture makeTexture(unsigned w, unsigned h, unsigned c, const void *pixels, bool isFloat)
{
	Texture retval = { 0 };
	
	GLenum f = 0, i = 0; // external and internal format for color storage

	switch (c)
	{
	case 0: f = GL_DEPTH_COMPONENT; i = GL_DEPTH24_STENCIL8; break;
	case 1: f = GL_RED;				i = GL_R32F;     break;
	case 2: f = GL_RG;				i = GL_RG32F;    break;
	case 3: f = GL_RGB;				i = GL_RGB32F;   break;
	case 4: f = GL_RGBA;			i = GL_RGBA32F; break;
	}
	
	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, ((isFloat || c==0)? i : f), w, h, 0, f,(isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE), pixels);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	return retval;
}

void freeTexture(Texture &t)
{
	glDeleteTextures(1, &t.handle);
	t = { 0 };
}

Framebuffer makeFramebuffer(unsigned w, unsigned h, unsigned c,
	bool hasDepth, unsigned nTargets, unsigned nFloatTargets)
{
	Framebuffer retval = { 0,w,h,nTargets+nFloatTargets,0,{0} };
	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);
	if (hasDepth)
	{
		retval.depthTarget = makeTexture(w, h, 0, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			retval.depthTarget.handle, 0);
	}
	const GLenum attachments[8] =
	{ 
		GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 
	};

	for (int i = 0; i < retval.nTargets && i < 8; ++i)
	{
		retval.targets[i] = makeTexture(w, h, c, 0, i >= nTargets);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.targets[i].handle, 0);
	}
	glDrawBuffers(retval.nTargets, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return retval;
}

void freeFrameBuffer(Framebuffer &fb);
