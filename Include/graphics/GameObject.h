#pragma once

#include "glm\glm.hpp"
#include "glm\ext.hpp"

#include "RenderObjects.h"

struct Camera
{
	glm::mat4 proj;
	glm::mat4 view;
};

struct SpecGloss
{
	Geometry geo;

	glm::mat4 model;
	Texture diffuse;
	Texture specular;
	Texture normal;
	float gloss;
};

struct StandardLight
{
	glm::vec3 dir;
	glm::vec4 color;
	float intensity;
	glm::vec4 ambient;
	int type;
};

struct DirectionalLight
{
	glm::vec3 target; // for shadow mapping
	float range;	  // for shadow mapping

	glm::vec3 direction;

	// 0
	glm::mat4 getProj() const
	{
		return glm::ortho<float>(-range, range, -range, range, -range, range);
	}

	// 1
	glm::mat4 getView() const
	{
		return glm::lookAt(-direction + target, target, glm::vec3(0, 1, 0));
	}

	glm::vec4 color; // 2
	float intensity; // 3
};

// just data!
struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 color;
	float size;
	float lifetime;
	float get_random(float min, float max) {

		return (max - min) * ((float)rand() / (float)RAND_MAX) + min;
	}
	glm::vec3 RandomVec = { get_random(-1.0f, 1.0f),get_random(-1.0f, 1.0f),get_random(-1.0f, 1.0f) };


};

class ParticleSystem
{


	float spawnTimer;
	float defaultTimer;
	float defaultSize;
	float defaultLifetime;
	float CountDown = 1;

public:
	const static unsigned int PARTICLE_COUNT = 1000;
	Particle particles[PARTICLE_COUNT];
	Geometry particleGeo;


	void init(float size, float lifetime, float timer);
	void update(float deltatime);
};

namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Camera &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const SpecGloss &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const DirectionalLight &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Particle &val);
}