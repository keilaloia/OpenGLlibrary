#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;
class ParticleSystem;
#include "glm\fwd.hpp"
enum RenderFlag
{
	NONE = 0,
	DEPTH = 1,
	ADDITIVE = 2,
};

void setFlags(int flags);

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);
void s0_draw(const Framebuffer &f, const Shader &s, const ParticleSystem &ps);

void setUniform(const Shader &s, int location, float value, int color); 
void setUniform(const Shader &s, int location, int key);
void setUniform(const Shader &s, int location, int value);
void setUniform(const Shader &s, int location, float value);

void setUniform(const Shader &s, int location, const glm::vec3 &val);
void setUniform(const Shader &s, int location, const glm::vec4 &val);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);

void setUniform(const Shader &s, int location, const glm::mat4 &val);

void clearFramebuffer(const Framebuffer & r, bool color = true, bool depth = true);

template<typename T, typename ...U>
void setUniforms(const Shader &s, int &loc_io, int &tex_io,
	const T &val, U &&... uniforms)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);

	// note that, the T parameter isn't a part of this call
	// it instead is stealing a value from the uniforms variadic
	setUniforms(s, loc_io, tex_io, uniforms...);
}

template<typename T>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);
}

namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val);

	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec3 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec4 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::mat4 &val);
}