#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"

#include "graphics\genShape.h"

int main()
{
	Context context;
	context.bInitialize(800, 600);
	// Initialize resources here!    

	Vertex verts[3] =
	{
		{ { -.5f,-.5f, 0, 1 },{ 1,0,0,1 } },
		{ { .5f,-.5f, 0, 1 },{ 0,1,0,1 } },
		{ { 0, .5f, 0, 1 },{ 0,0,1,1 } }
	};

	unsigned idxs[3] = { 0,1,2 };

	Geometry g = makeGeometry(verts, 3, idxs, 3);
	Geometry gt = makeCheckerboard(2, .25f);
	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 0) uniform float time; \n"
		"layout(location = 3) in vec2 uv;"
		"out vec2 vuv;"
		"out vec4 vPos; \n"
		"flat out vec4 vColor;\n"
		"void main () \n"
		"{ \n"
		"gl_Position = position; gl_Position.y += cos(time + position.x) / 5.0;\n"
		"vPos = position; vuv = uv; }\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec4 vPos; \n"
		"in vec2 vuv;"
		"layout(location = 0) uniform float time; \n"
		"layout(location = 1) uniform int key; \n"
		"layout(location = 2) uniform sampler2D map;"
		

		"flat in vec4 vColor;\n"
		"void main () "
		"{\n"
		
		"outColor = texture(map, vuv * sin(time));\n"
		"}\n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };

	unsigned char pixels[] = { 300,0,255, 300,255,0 };
	Texture t_magyel = makeTexture(1, 2, 3, pixels);

	while (context.bUpdate()) // The game loop
	{
		clearFramebuffer(f);
		setUniform(s, 0, (float)context.dgetTime());
		setUniform(s, 1 ,(int)context.bgetkey('A'));
		setUniform(s, 2, t_magyel, 0);

		s0_draw(f, s, g);
	}

	// Free resources here!

	context.bTerminate();
	return 0;
}