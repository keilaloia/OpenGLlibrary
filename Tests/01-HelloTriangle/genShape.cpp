#include "graphics\genShape.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "glm\glm.hpp"


Geometry makeNGon(size_t sides, float r)
{
	//number of vertices (sides + 1)
	unsigned vsize = 0; // how big should this be?

	//number of triangles * 3
	unsigned isize = 0; // how big should this be?
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);
	delete[] verts;
	delete[] idxs;

	return ret;  
}

Geometry makeCheckerboard(int dim, float size)
{
	unsigned vdim = dim + 1;
	unsigned vsize = vdim*vdim;
	unsigned isize = 3 * 2 * dim * dim;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float step = dim / size;
	float offset = size / 2;

	int l = 0;

	for (int i = 0; i < vsize; ++i)
	{
		float x = (i % vdim) *step - offset;
		float y = (i / vdim) *step - offset;

		verts[i].position = { x,y,0,1 };
		verts[i].color    = { rand()/(float)RAND_MAX,rand() / (float)RAND_MAX,0,1 };

		if (i == 1 && dim > 1 || i % vdim != 1 && i / vdim != vdim - 1 && l < isize)
		{

		
			idxs[l++] = i;
			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;
		/*
			i;
			i + vdim;
			i + vdim + 1;*/
		}
	}
	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return ret;
}