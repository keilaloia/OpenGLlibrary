#pragma once
#include "glm\glm.hpp"

struct Geometry;

Geometry makeNGon(size_t sides, float r);
Geometry makeCheckerboard(int dim, float size);
