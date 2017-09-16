#include "graphics\GameObject.h"

#include "graphics\vertex.h"
#include "graphics\RenderObjects.h"
#include <random>
#include "GL\glew.h"
#include "glm\ext.hpp"
#include "utility.h"
#include <cmath>


void ParticleSystem::init(float size, float lifetime, float timer)
{
	defaultTimer = timer;
	defaultSize = size;
	defaultLifetime = lifetime;
	spawnTimer = 0.0f;
}

void ParticleSystem::update(float deltaTime)
{
	// should we emit?
	
	spawnTimer += deltaTime;
	CountDown -= deltaTime;
	if (spawnTimer > defaultTimer)
	{
		// find the first available particle
		for (int i = 0; i < PARTICLE_COUNT; ++i)
		{
			if (particles[i].lifetime <= 0.0f)
			{
				// bring that particle to life
				particles[i].lifetime = defaultLifetime;
				particles[i].lifespan = defaultLifetime;
				particles[i].position = { 0,0,0 };
				particles[i].velocity = glm::vec3(rand(-1.0f, 1.0f), rand(-1.0f, 1.0f), rand(-1.0f, 1.0f));

				particles[i].currentColor = glm::vec4(rand(0.0f, 1.0f), rand(0.0f, 1.0f),
													  rand(0.0f, 1.0f), rand(0.0f, 1.0f));
				particles[i].startColor = particles[i].currentColor;
				particles[i].targetColor = glm::vec4(rand(0.0f, 1.0f),rand(0.0f, 1.0f),
													 rand(0.0f, 1.0f),rand(0.0f, 1.0f));
				particles[i].size = defaultSize;
				particles[i].lastChangeTime = particles[i].lifetime;

				spawnTimer = 0.0f;
				break;
			}
		}
		
	}
	
	// simulate

	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		if (particles[i].lifetime > 0.0f)
		{
			float lifeRatio = particles[i].lifetime / particles[i].lifespan;

			if (particles[i].lastChangeTime - particles[i].lifetime > 1)
			{
				particles[i].lastChangeTime -= 1;

				particles[i].startColor = particles[i].currentColor;
				particles[i].targetColor = glm::vec4(rand(0.0f, 1.0f), rand(0.0f, 1.0f),
												     rand(0.0f, 1.0f), rand(0.0f, 1.0f));
			}

			particles[i].currentColor = glm::lerp(particles[i].targetColor, particles[i].startColor, lifeRatio);
			particles[i].size = defaultSize * lifeRatio;
			particles[i].lifetime -= deltaTime;
			particles[i].position += particles[i].velocity * deltaTime;
		}
	}
}
