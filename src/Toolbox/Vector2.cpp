#include "Vector2.h"
#include <random>
#include <math.h>

Vector2::Vector2(float v0, float v1)
	: m_v0(v0), m_v1(v1) {}

Vector2::Vector2(bool random)
{
	if (random)
		randomizeVector();
	else
	{
		m_v0 = 0.0f;
		m_v1 = 0.0f;
	}
}

Vector2::Vector2(const Vector2& v)
{
	m_v0 = v.v0();
	m_v1 = v.v1();
}

void Vector2::randomizeVector()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);
	int r = dis(gen) % 4;
	switch (r)
	{
	case 0:
		m_v0 = 1.0f; m_v1 = 1.0f;
		break;
	case 1:
		m_v0 = -1.0f; m_v1 = 1.0f;
		break;
	case 2:
		m_v0 = 1.0f; m_v1 = -1.0f;
		break;
	case 3:
		m_v0 = -1.0f; m_v1 = -1.0f;
		break;
	}
}

double Vector2::distance(const Vector2& from, const Vector2& target)
{
	return sqrt(pow(target.v0() - from.v0(), 2) + pow(target.v1() - from.v1(), 2));
}

Vector2 Vector2::getDisplacementVector(Vector2 vec, int yBound, int xBound)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);
	int yDisplacement = (dis(gen) % (yBound - 1)) + 1;
	int xDisplacement = (dis(gen) % (xBound - 1)) + 1;

	switch ((dis(gen) % 3) + 1)
	{
	case 1:
		yDisplacement = -yDisplacement;
		break;
	case 2:
		xDisplacement = -xDisplacement;
		break;
	case 3:
		yDisplacement = -yDisplacement;
		xDisplacement = -xDisplacement;
		break;
	}

	return Vector2(vec.v0() + yDisplacement, vec.v1() + xDisplacement);
}
