#include "graphics\load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Context.h"
#include "graphics\draw.h"


#include "glm\ext.hpp"



void main()
{
	Context context;
	context.bInitialize();


	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1, 1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/cube.obj");

	Texture tex = loadTexture("../../resources/textures/horse.png");


	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 2) in vec2 texCoord;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{ gl_Position = position; vUV = texCoord; }\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec2 vUV;\n"
		"layout(location = 0) uniform sampler2D map;\n"
		"void main () { outColor = texture(map, vUV.xy); }\n";

	Shader sq = makeShader(vsource, fsource);
	// initialization and file loading goes

	
	Shader stest = loadShader("../../resources/shader/test.vert", "../../resources/shader/test.frag");

	Framebuffer screen = { 0,800,600 };
	setFlags(RenderFlag::DEPTH);

	glm::mat4 model;

	while (context.bUpdate())
	{
		clearFramebuffer(screen);
		float time = context.dgetTime();

		model = glm::rotate(time, glm::vec3(0, 1, 0));

		setUniform(stest, 0, tex, 0);
		setUniform(stest, 1, model);
		s0_draw(screen, stest, cube);
		// and uniforms
		// draw and update stuff goes
		
	}

	freeTexture(tex);
	freeShader(sq);
	freeGeometry(quad);
	// destroying stuff goes


	context.bTerminate();
}