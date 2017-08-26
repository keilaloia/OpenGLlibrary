#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;
#include "glm\fwd.hpp"
enum RenderFlag { DEPTH = 1};

void setFlags(int flags);

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);

void setUniform(const Shader &s, int location, float value, int color); 
void setUniform(const Shader &s, int location, int key);
void setUniform(const Shader &s, int location, int value);
void setUniform(const Shader &s, int location, float value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);

void setUniform(const Shader &s, int location, const glm::mat4 &val);

void clearFramebuffer(const Framebuffer & r, bool color = true, bool depth = true);