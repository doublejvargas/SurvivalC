#pragma once

#include "Vector2.h"
#include <vector>
#include "cstdlib"

class PerlinNoise2D
{
public:
	PerlinNoise2D(int w, int h);
	void Init();

	float Value(float x, float y);
private:
	float DotProduct(const Vector2& v1, const Vector2& v2);
	std::vector<Vector2> m_Gradients;
	//std::vector<Vector2> m_Indices;
	int m_WIDTH;
	int m_HEIGHT;
	int WRAP_SIZE = 256;
};
