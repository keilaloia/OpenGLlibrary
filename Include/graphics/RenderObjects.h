#pragma once
#include "glm\glm.hpp"

struct Vertex;
struct Geometry
{
	unsigned handle, //Vertex Array Object used to draw
		vbo, //Vertex buffer
		ibo, //Index buffer
		size; // how many indices ake up this model
};

Geometry makeGeometry(const Vertex *vertices, size_t vsize,
					  const unsigned *indices, size_t isize);

void freeGeometry(Geometry &g);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);
void freeShader(Shader &);

struct Framebuffer
{
	unsigned handle, width, height;
};


struct Texture
{
	unsigned handle;
};

Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char *pixels);

void freeTexture(Texture &t);
