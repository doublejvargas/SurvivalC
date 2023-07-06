#include "Vector2.h"
#include <random>
#include <math.h>

Vector2::Vector2(float v0, float v1)
	: m_v0(v0), m_v1(v1) {}

double Vector2::distance(const Vector2& target)
{
	return sqrt(pow(target.v0() - m_v0, 2) + pow(target.v1() - m_v1, 2));
}

Vector2 Vector2::getDisplacementVector(int yBound, int xBound)
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

	return Vector2(m_v0 + yDisplacement, m_v1 + xDisplacement);
}

bool operator==(const Vector2 v1, const Vector2 v2)
{
	return (v1.m_v0 == v2.m_v0 &&
		v1.m_v1 == v2.m_v1);
}
