#include "graphics\load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Context.h"
#include "graphics\draw.h"

#include "glm\ext.hpp"

void main()
{
	Context context;

	context.bInitialize(1280,720);


	// Floor
	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
		* glm::scale(glm::vec3(5, 5, 1));

	// SoulSpear
	Geometry  ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model; // = glm::rotate(time, glm::vec3(0,1,0)) // on update.

						// Cube
	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));

	// Shaders
	Shader shdr_shadow = loadShader("../../resources/shader/shadow.vert",
		"../../resources/shader/shadow.frag");
	Shader shdr_direct = loadShader("../../resources/shader/direct.vert",
		"../../resources/shader/direct.frag");

	//////////////////////////
	// Camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 5),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);

	// Light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8, -1, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));



	// Buffers
	Framebuffer fb_shadow = makeFramebuffer(2048, 2048, 0, true, 0, 0);
	Framebuffer screen = { 0,1280, 720 };

	

	while (context.bUpdate())
	{
		float time = context.dgetTime();
		ss_model = glm::rotate(time, glm::vec3(0, 1, 0));
		

		//Shadow Pass
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fb_shadow, false, true);

		int loc = 0, slot = 0;
		
		setUniform(shdr_shadow, 0, light_proj);
		setUniform(shdr_shadow, 1, light_view);
		setUniform(shdr_shadow, 2, floor_model);
		s0_draw(fb_shadow, shdr_shadow, floor_geo);

		loc = slot = 0;

		setUniform(shdr_shadow, 0, light_proj);
		setUniform(shdr_shadow, 1, light_view);
		setUniform(shdr_shadow, 2, ss_model);
		s0_draw(fb_shadow, shdr_shadow, ss_geo);

		loc = slot = 0;

		setUniform(shdr_shadow, 0, light_proj);
		setUniform(shdr_shadow, 1, light_view);
		setUniform(shdr_shadow, 2, cube_model);
		s0_draw(fb_shadow, shdr_shadow, cube_geo);


		// Light Pass		
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		loc = slot = 0;

		setUniform(shdr_direct, 0, cam_proj);
		setUniform(shdr_direct, 1, cam_view);
		setUniform(shdr_direct, 2, floor_model);
		setUniform(shdr_direct, 3, light_proj);
		setUniform(shdr_direct, 4, light_view);
		setUniform(shdr_direct, 5, fb_shadow.depthTarget, 0);
		s0_draw(screen, shdr_direct, floor_geo);

		loc = slot = 0;

		setUniform(shdr_direct, 0, cam_proj);
		setUniform(shdr_direct, 1, cam_view);
		setUniform(shdr_direct, 2, ss_model);
		setUniform(shdr_direct, 3, light_proj);
		setUniform(shdr_direct, 4, light_view);
		setUniform(shdr_direct, 5, fb_shadow.depthTarget,0);
		s0_draw(screen, shdr_direct, ss_geo);

		loc = slot = 0;
		setUniform(shdr_direct, 0, cam_proj);
		setUniform(shdr_direct, 1, cam_view);
		setUniform(shdr_direct, 2, cube_model);
		setUniform(shdr_direct, 3, light_proj);
		setUniform(shdr_direct, 4, light_view);
		setUniform(shdr_direct, 5, fb_shadow.depthTarget,0);
		s0_draw(screen, shdr_direct, cube_geo);


	}
	context.bTerminate();
}