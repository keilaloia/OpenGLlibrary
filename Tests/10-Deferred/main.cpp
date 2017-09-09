#include "graphics\GameObject.h"
#include "graphics\Vertex.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"
#include "graphics\Context.h"
#include "graphics\draw.h"


void main()
{
	Context context;
	context.bInitialize(1280, 720);

	Vertex vquad[] = { { { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };
	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	//////////////////////////////////////////////
	// Game objects/geometry
	SpecGloss objects[8];

	// floor
	objects[0].geo = quad;

	objects[0].model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
		* glm::scale(glm::vec3(5, 5, 1));

	objects[0].diffuse = loadTexture("../../resources/textures/four_diffuse.tga");
	objects[0].specular = loadTexture("../../resources/textures/four_specular.tga");
	objects[0].normal = loadTexture("../../resources/textures/four_normal.tga");
	objects[0].gloss = 4;


	// Soulspear
	objects[1].geo = loadGeometry("../../resources/models/soulspear.obj");
	objects[1].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	objects[1].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	objects[1].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	objects[1].gloss = 4;

	// Earth
	objects[2].geo = loadGeometry("../../resources/models/sphere.obj");
	objects[2].diffuse = loadTexture("../../resources/textures/earth_diffuse.jpg");
	objects[2].specular = loadTexture("../../resources/textures/earth_specular.jpg");
	objects[2].normal = loadTexture("../../resources/textures/earth_normal.jpg");
	objects[2].gloss = 4;
	objects[2].model = glm::scale(glm::vec3(2, 2, 2)) * glm::translate(glm::vec3(2, 1, -1));

	// Camera
	Camera cam;
	cam.view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);

	DirectionalLight dlights[2];

	dlights[0].range = 10;
	dlights[0].intensity = 1;
	dlights[0].color = glm::vec4(1, 1, 0, 1);
	dlights[0].direction = glm::vec3(1, 0, 0);

	dlights[1].range = 10;
	dlights[1].intensity = 1;
	dlights[1].color = glm::vec4(0, 0, 1, 1);
	dlights[1].direction = glm::vec3(-1, 0, 0);

	Shader gpass = loadShader("../../resources/shader/gpass.vert", "../../resources/shader/gpass.frag");
	Shader cpass = loadShader("../../resources/shader/cpass.vert", "../../resources/shader/cpass.frag");
	Shader IpassD = loadShader("../../resources/shader/IpassD.vert", "../../resources/shader/IpassD.frag");

	Framebuffer screen = { 0,1280,720 };
	Framebuffer gbuffer = makeFramebuffer(1280, 720, 4, true, 2, 2);
	Framebuffer Ibuffer = makeFramebuffer(1280, 720, 4, false, 2, 0);

	int loc = 0, slot = 0;
	while (context.bUpdate())
	{
		////////////////////////////
		// GPass
		clearFramebuffer(gbuffer);
		setFlags(RenderFlag::DEPTH);
		for (int i = 0; i < 3; ++i)
		{
			loc = slot = 0;
			setUniforms(gpass, loc, slot, cam, objects[i]);
			s0_draw(gbuffer, gpass, objects[i].geo);
		}
		////////////////////////////
		// LPass
		clearFramebuffer(Ibuffer);
		setFlags(RenderFlag::ADDITIVE);
		for (int i = 0; i < 2; ++i)
		{
			loc = slot = 0;
			setUniforms(IpassD, loc, slot, cam, dlights[i], gbuffer.targets[3]);
			s0_draw(Ibuffer, IpassD, quad);
		}

		////////////////////////////
		// CPass
		loc = slot = 0;
		clearFramebuffer(screen);
		setUniforms(cpass, loc, slot, gbuffer.targets[0], Ibuffer.targets[0]);
 		s0_draw(screen, cpass, quad);
	}
	context.bTerminate();
}