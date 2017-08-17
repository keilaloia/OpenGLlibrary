#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"

int main()
{
	Context context;
	context.bInitialize(800, 600);
	// Initialize resources here!    

	Vertex verts[3] = 
	{ 
	{ { -.5f,-.5f, 0, 1 }, {1,0,0,1} },
	{ { .5f,-.5f, 0, 1 },{0,1,0,1} },
	{ { 0, .5f, 0, 1 },{0,0,1,1} }
	};

	unsigned idxs[3] = { 0,1,2 };

	Geometry g = makeGeometry(verts, 3, idxs, 3);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vColor;\n"
		"void main () { gl_Position = position; vColor = color; }\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec4 vColor;\n"
		"void main () { outColor = vColor; }\n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };
	while (context.bUpdate()) // The game loop
	{
		s0_draw(f, s, g);
	}

	// Free resources here!

	context.bTerminate();
	return 0;
}