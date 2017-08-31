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

	Vertex vquad[] =
	{
		{ { -1,-1,0,1 },{},{ 0,0 }, {0,0,1,0} },
		{ { 1,-1,0,1 },{},{ 1,0 }, { 0, 0,1, 0}},
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Texture normal_face = loadTexture("../../resources/textures/normal_face.png");
	Texture color = loadTexture("../../resources/textures/horse.png");

	Shader standard = loadShader("../../resources/shader/standard.vert",
								 "../../resources/shader/standard.frag");

	Framebuffer screen = { 0, 800, 600 };

	//camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4),
									 glm::vec3(0, 1, 0),
									 glm::vec3(0, 1, 0));

	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	// Model
	glm::mat4 go_model;

	// Light
	glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));

	while (context.bUpdate())
	{
		float time = context.dgetTime();
		go_model = glm::rotate(time, glm::vec3(1, 0, 0));

		
		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;

		setUniform(standard, 0, cam_proj);
		setUniform(standard, 1, cam_view);
		setUniform(standard, 2, go_model);
		setUniform(standard, 3, normal_face, 0);
		setUniform(standard, 4, color, 0);
		setUniform(standard, 5, light_direction);


	

		s0_draw(screen, standard, quad);
	}
	context.bTerminate();
}