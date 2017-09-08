#include "graphics\load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\GameObject.h"

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

	Shader standard = loadShader("../../resources/shader/standard.vert",
								 "../../resources/shader/standard.frag");

	Shader fsq_shader = loadShader("../../resources/shader/quad.vert",
								   "../../resources/shader/quad.frag");

	Framebuffer screen = { 0,1280,720 };
	Framebuffer fBuffer = makeFramebuffer(1280, 720, 4, true, 3, 1);

	//////////////////////////////////////////
	//model data 
	SpecGloss sceneObject[2];

	sceneObject[0].geo =  loadGeometry("../../resources/models/soulspear.obj");
	sceneObject[0].model;
	
	sceneObject[0].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	sceneObject[0].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	sceneObject[0].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	sceneObject[0].gloss = 4.0f;


	sceneObject[1].geo = loadGeometry("../../resources/models/soulspear.obj");
	sceneObject[1].model;

	sceneObject[1].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	sceneObject[1].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	sceneObject[1].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	sceneObject[1].gloss = 4.0f;

	///////////////////////////////////////////
	//camera
	Camera cam;
	cam.view = glm::lookAt(glm::vec3(0, 2, 3),
									 glm::vec3(0, 2, 0),
									 glm::vec3(0, 1, 0));

	cam.proj = glm::perspective(45.f, 800.f / 600.f, 0.01f, 100.f);


	///////////////////////////////////////////
	// Model
	glm::mat4 go_model;

	///////////////////////////////////////////
	// Light
	glm::vec3 l_Dir = glm::normalize(glm::vec3(1, -1, -1));
	glm::vec4 l_Color		  = glm::vec4( .7, .6, .9, 1 );
	float l_intensity		  = 1.0;
	glm::vec4 l_ambient		  = glm::vec4(.2,.2,.01,1);
	int l_type				  = 0;







	while (context.bUpdate())
	{
		float time = context.dgetTime();
		sceneObject[0].model = glm::rotate(time, glm::vec3(0, 1, 0));

		
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fBuffer);
		int loc = 0, slot = 0;

		setUniform(standard, 0, cam.proj);
		setUniform(standard, 1, cam.view);
		setUniform(standard, 2, sceneObject[0].model);
		setUniform(standard, 3, sceneObject[0].diffuse, 0);
		setUniform(standard, 4, sceneObject[0].specular, 1);
		setUniform(standard, 5, sceneObject[0].normal, 2);
		setUniform(standard, 6, sceneObject[0].gloss);
		setUniform(standard, 7, l_Dir);
		setUniform(standard, 8, l_Color);
		setUniform(standard, 9, l_intensity);
		setUniform(standard, 10, l_ambient);
		setUniform(standard, 11, l_type);
		s0_draw(fBuffer, standard, sceneObject[0].geo);

		setUniform(standard, 0, cam.proj);
		setUniform(standard, 1, cam.view);
		setUniform(standard, 2, sceneObject[1].model);
		setUniform(standard, 3, sceneObject[1].diffuse, 0);
		setUniform(standard, 4, sceneObject[1].specular, 1);
		setUniform(standard, 5, sceneObject[1].normal, 2);
		setUniform(standard, 6, sceneObject[1].gloss);
		setUniform(standard, 7, l_Dir);
		setUniform(standard, 8, l_Color);
		setUniform(standard, 9, l_intensity);
		setUniform(standard, 10, l_ambient);
		setUniform(standard, 11, l_type);



		s0_draw(fBuffer, standard, sceneObject[1].geo);



		clearFramebuffer(screen);
		loc = 0, slot = 0;	
		/*setUniform(fsq_shader, 0, loc);
		setUniform(fsq_shader, 1, slot);*/
		setUniform(fsq_shader, 0, fBuffer.targets[3], 0);
		setUniform(fsq_shader, 1, fBuffer.targets[3], 0);


		s0_draw(screen, fsq_shader, quad);



	}
	context.bTerminate();
}