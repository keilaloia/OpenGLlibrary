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

	Geometry ss_geo = loadGeometry("../resources/models/soulspear.obj");
	Texture ss_diffuse = loadTexture("../resources/textures/soulspear_diffuse.tga");
	Shader mvplite = loadShader("../resources/shaders/mvplite.vert", "../resources/shaders/mvplite.frag");

	Framebuffer screen = { 0,800,600 };

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
	glm::mat4 go_model; // identity matrix for now

	while (context.bUpdate())
	{
		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);
		
		int loc = 0, slot = 0;
		//setUniform(lambert, loc, tslot, cam_view, cam_proj, go_model, ss_diffuse);

		//s0_draw(screen, lambert, ss_geo);
		// and uniforms
		// draw and update stuff goes

	}
}