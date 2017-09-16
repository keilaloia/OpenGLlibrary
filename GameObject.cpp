#include "graphics\GameObject.h"
#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Load.h"

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const SpecGloss & val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val.model);
	__internal::t_setUniform(s, loc_io, tex_io, val.diffuse);
	__internal::t_setUniform(s, loc_io, tex_io, val.specular);
	__internal::t_setUniform(s, loc_io, tex_io, val.normal);
	__internal::t_setUniform(s, loc_io, tex_io, val.gloss);
}

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Camera & val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val.proj);
	__internal::t_setUniform(s, loc_io, tex_io, val.view);
}

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const DirectionalLight & val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val.getProj());
	__internal::t_setUniform(s, loc_io, tex_io, val.getView());
	__internal::t_setUniform(s, loc_io, tex_io, val.color);
	__internal::t_setUniform(s, loc_io, tex_io, val.intensity);
}

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Particle & val)
{
	__internal::t_setUniform(s, loc_io, tex_io, glm::translate(val.position) * glm::scale(glm::vec3(val.size, val.size, val.size)));
	__internal::t_setUniform(s, loc_io, tex_io, val.currentColor);
}
