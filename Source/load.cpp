#include "Graphics\load.h"
#include "graphics\RenderObjects.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "graphics\Vertex.h"

#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include "STB\stb_image.h"
#include "obj\tiny_obj_loader.h"

Texture loadTexture(const char *path)
{
	Texture retval = { 0 };

	//put in some code
	stbi_set_flip_vertically_on_load(true);

	//putting up the parameters for the texture
	int w, h, c;
	unsigned char *pixels;
	pixels = stbi_load(path, &w, &h, &c, STBI_default);

	//calling make texture function
	retval = makeTexture(w, h, c, pixels);
	stbi_image_free(pixels);
	return retval;
}

//read that file
//std::string readFile(const char *filePath)
//{
//	std::string content;
//	std::ifstream fileStream(filePath, std::ios::in);
//
//	if (!fileStream.is_open())
//	{
//		std::cerr << "Could not read file" << filePath << ". File does not exist." << std::endl;
//		return "";
//	}
//	std::string line = "";
//	while (!fileStream.eof())
//	{
//		std::getline(fileStream, line);
//		content.append(line + "\n");
//	}
//
//	fileStream.close();
//	return content;
//
//}





Shader loadShader(const char *v_path, const char *f_path)
{
	Shader retval = { 0 };

	std::ifstream v;
	v.open(v_path);

	assert(v.good() && "not good");

	std::string vstr;
	v.seekg(0, v.end);
	int val = v.tellg();
	vstr.reserve(v.tellg());
	v.seekg(0, v.beg);

	vstr.assign((std::istreambuf_iterator<char>(v)),
		std::istreambuf_iterator<char>());

	std::ifstream f(f_path);

	assert(f.good() && "not good");

	std::string fstr;
	f.seekg(0, f.end);
	fstr.reserve(f.tellg());
	f.seekg(0, f.beg);

	fstr.assign((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());

	retval = makeShader(vstr.c_str(), fstr.c_str());

	return retval;
	
}

Geometry loadGeometry(const char *path)
{
	Geometry retval = { 0,0,0,0 };
	tinyobj::attrib_t attrib;				// Vertex Data is stored.
	std::vector<tinyobj::shape_t> shapes;	// Triangular data, indices.
	std::vector<tinyobj::material_t> materials;
	std::string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	/////////////////////////////////////////////////////////////////
	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];

	size_t vsize = isize;
	Vertex *verts = new Vertex[vsize];

	for (int i = 0; i < isize; ++i)
	{
		indices[i] = i;

		int pi = shapes[0].mesh.indices[i].vertex_index;
		int ni = shapes[0].mesh.indices[i].normal_index;
		int ti = shapes[0].mesh.indices[i].texcoord_index;

		const float *p = &attrib.vertices[pi * 3];  // 3x
		const float *n = &attrib.normals[ni * 3];   // 3x
		const float *t = &attrib.texcoords[ti * 2]; // 2x

		verts[i].position = { p[0],p[1],p[2],1 };
		verts[i].texCoord = { t[0],t[1] };
		verts[i].normal = { n[0],n[1],n[2],0 };
	}
	///////////////////////////////////////////////////////////////////

	solveTangents(verts, vsize, indices, isize);

	retval = makeGeometry(verts, vsize, indices, isize);

	delete[] verts;
	delete[] indices;
	return retval;
}
