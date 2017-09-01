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

	Shader standard = loadShader("../../resources/shader/standard.vert",
								 "../../resources/shader/standard.frag");

	Shader fsq_shader = loadShader("../../resources/shader/quad.vert",
								   "../../resources/shader/quad.frag");

	Framebuffer screen = { 0,1280,720 };
	Framebuffer fBuffer = makeFramebuffer(1280, 720, 4, true, 3, 1);

	//////////////////////////////////////////
	//model data 
	Geometry  ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;
	
	Texture ss_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture ss_specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	float ss_gloss = 4.0f;

	
	///////////////////////////////////////////
	//camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 3),
									 glm::vec3(0, 2, 0),
									 glm::vec3(0, 1, 0));

	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, 0.01f, 100.f);


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
		ss_model = glm::rotate(time, glm::vec3(0, 1, 0));

		
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fBuffer);
		int loc = 0, slot = 0;

		setUniform(standard, 0, cam_proj);
		setUniform(standard, 1, cam_view);
		setUniform(standard, 2, ss_model);
		setUniform(standard, 3, ss_diffuse, 0);
		setUniform(standard, 4, ss_specular, 1);
		setUniform(standard, 5, ss_normal, 2);
		setUniform(standard, 6, ss_gloss);
		setUniform(standard, 7, l_Dir);
		setUniform(standard, 8, l_Color);
		setUniform(standard, 9, l_intensity);
		setUniform(standard, 10, l_ambient);
		setUniform(standard, 11, l_type);

	

		s0_draw(fBuffer, standard, ss_geo);



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