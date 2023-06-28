#pragma once

#include "Vector2.h"
#include <vector>
#include "cstdlib"

#define WRAP_SIZE 256

class PerlinNoise2D
{
public:
	void init();

	float value(float x, float y);
private:
	float DotProduct(const Vector2& v1, const Vector2& v2);
	std::vector<Vector2> m_Gradients;
};
