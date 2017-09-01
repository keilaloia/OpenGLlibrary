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

void solveTangents(Vertex *v, size_t vsize,
							 const unsigned *idx, size_t isize);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);
void freeShader(Shader &);


struct Texture
{
	unsigned handle;
};

Texture makeTexture(unsigned w, unsigned h, unsigned c,
					const void *pixels, bool isFloat = false);

void freeTexture(Texture &t);

struct Framebuffer
{
	unsigned handle, width, height, nTargets;
	Texture depthTarget;
	Texture targets[8];
};

Framebuffer makeFramebuffer(unsigned w, unsigned h, unsigned c,
						    bool hasDepth, unsigned nTargets, unsigned nFloatTargets);

void freeFrameBuffer(Framebuffer &fb);
