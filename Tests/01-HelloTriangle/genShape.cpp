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