#include "graphics\GameObject.h"

#include "graphics\vertex.h"
#include "graphics\RenderObjects.h"
#include <random>


void ParticleSystem::init(float size, float lifetime, float timer)
{
	defaultTimer = timer;
	defaultSize = size;
	defaultLifetime = lifetime;
	spawnTimer = 0.0f;

	// initialize particles
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		particles[i].lifetime = 0.0f;
	}
}

void ParticleSystem::update(float deltaTime)
{
	// should we emit?
	float lifeRatio;
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
				lifeRatio = particles[i].lifetime / defaultLifetime;
				particles[i].position = { 0,0,0 };
				particles[i].velocity = particles[i].RandomVec;			
				particles[i].color = { particles[i].get_random(0.0f, 1.0f) * lifeRatio,particles[i].get_random(0.0f, 1.0f) * lifeRatio,
									   particles[i].get_random(0.0f, 1.0f) * lifeRatio,particles[i].get_random(0.0f, 1.0f) * lifeRatio };
				particles[i].size = defaultSize;

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
			lifeRatio = particles[i].lifetime / defaultLifetime;
			if (CountDown < 0.0f)
			{
				for (int j = 0; j < PARTICLE_COUNT; j++)
				{
					particles[j].color = { particles[j].get_random(0.0f, 1.0f) ,particles[j].get_random(0.0f, 1.0f) ,
										   particles[j].get_random(0.0f, 1.0f) ,particles[j].get_random(0.0f, 1.0f) };
				}
				
				CountDown = 1;
				break;
			}
			

			particles[i].size = defaultSize * lifeRatio;
			particles[i].lifetime -= deltaTime;
			particles[i].position += particles[i].velocity * deltaTime;
		}
	}
}
