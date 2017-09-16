#pragma once

#include <random>

float inline rand(float min, float max)
{
	return (max - min) * ((float)rand() / (float)RAND_MAX) + min;
}