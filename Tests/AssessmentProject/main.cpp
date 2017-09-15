#include "graphics\GameObject.h"
#include "graphics\load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include "glm\ext.hpp"
#include <iostream>
#include <math.h>
#include <vector>

////////////////////////////
///GL CHEAT SHEAT
//GenBuffers - allocate space in graphics card
//BindBuffer - Binding access to that memory spot like adding a wire
//BufferData - filling that memory space with data now
//BufferSubData - only fills in part of that memory hole
////////////////////////////



void main()
{
	Context context;
	context.bInitialize(1280, 720);

	// Camera
	Camera cam;
	cam.view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10000.f);

	Shader psShader = loadShader("../../resources/shader/Assesment.vert", "../../resources/shader/Assesment.frag");
	
	Vertex vert[1] = {};
	unsigned int idx[1] = { 0 };

	Vertex vquad[] = { { { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };
	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Framebuffer screen = { 0,1280,720 };

	ParticleSystem particleSystem;
	particleSystem.init(0.2f, 3.0f, 0.1f);
	particleSystem.particleGeo = quad;// makeGeometry(vert, 1, idx, 1);

	float prevTime = context.dgetTime();

	int loc = 0, slot = 0;
	while (context.bUpdate())
	{
		float deltaTime = context.dgetTime() - prevTime;
		prevTime = context.dgetTime();

		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		particleSystem.update(deltaTime);

		for (int i = 0; i < ParticleSystem::PARTICLE_COUNT; ++i)
		{
			if (particleSystem.particles[i].lifetime > 0)
			{
				int loc = 0, tex = 0;
				setUniforms(psShader, loc, tex, cam, particleSystem.particles[i]);
				s0_draw(screen, psShader, particleSystem.particleGeo);
			}
		}
	}
	context.bTerminate();
}