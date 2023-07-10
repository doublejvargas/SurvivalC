#include "PerlinNoise2D.h"
#include <random>
#include <math.h>

void PerlinNoise2D::init()
{
	Vector2 grad[4] = {
		{1,	 0},
		{0,	 1},
		{-1, 0},
		{0, -1}
	};

	//m_Gradients.reserve(WRAP_SIZE * WRAP_SIZE);
	m_Gradients = std::vector<Vector2>(WRAP_SIZE * WRAP_SIZE, Vector2(0, 0));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 99);
	for (uint32_t i = 0; i < WRAP_SIZE * WRAP_SIZE; i++)
	{
		m_Gradients[i] = grad[dis(gen) % 4];
	}

}

float PerlinNoise2D::value(float x, float y)
{
	// integer part
	int ix = (int)x;
	int iy = (int)y;
	// fraction part
	float fx = x - ix;
	float fy = y - iy;

	// wrap around
	ix = ix % WRAP_SIZE;
	iy = iy % WRAP_SIZE;

	// (x, y)		(x+1, y)
	//			P
	//
	//(x, y+1)		(x+1, y+1)
	// get nearest gradients
	Vector2 pTL = m_Gradients[iy * WRAP_SIZE + ix];
	Vector2 pTR = m_Gradients[iy * WRAP_SIZE + (ix + 1)];
	Vector2 pBL = m_Gradients[(iy + 1) * WRAP_SIZE + ix];
	Vector2 pBR = m_Gradients[(iy + 1) * WRAP_SIZE + (ix + 1)];

	// find distance from gradients
	Vector2 dTL = { fx,		fy };
	Vector2 dTR = { fx - 1, fy };
	Vector2 dBL = { fx,		fy - 1 };
	Vector2 dBR = { fx - 1, fy - 1};

	// calculate dot product for each corner
	float fTL = DotProduct(pTL, dTL);
	float fTR = DotProduct(pTR, dTR);
	float fBL = DotProduct(pBL, dBL);
	float fBR = DotProduct(pBR, dBR);

	//linear interpolation
	auto lerp = [](float& a, float& b, float w)
	{
		return w * (b - a) + a;
	};

	// smoothing function: 6t^5 - 15t^4 + 10t^3
	//                    = t^3(6t^2 - 15t + 10)
	auto smooth = [](float t)
	{
		return t * t * t * ((6 * t * t) - (15 * t) + 10);
	};

	fx = smooth(fx);
	fy = smooth(fy);
	
	// interpolate
	float fL = lerp(fTL, fBL, fy);
	float fR = lerp(fTR, fBR, fy);
	
	//final perlin value range [-1, 1]
	float pVal = lerp(fL, fR, fx);

	return pVal;
}

float PerlinNoise2D::DotProduct(const Vector2& v1, const Vector2& v2)
{
	//A dot B = ax * bx + ay * by
	return v1.v1() * v2.v1() + v1.v0() * v2.v0();
}

