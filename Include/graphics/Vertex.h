#pragma once

#include "glm\glm.hpp"

struct Vertex
{
	glm::vec4 position; // 0, 4 floats (4 bytes) = 16 bytes
	glm::vec4 color;	// 16
	glm::vec2 texCoord;
	glm::vec4 normal;
};