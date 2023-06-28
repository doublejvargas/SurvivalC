#include "Vector2.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

Vector2::Vector2(float y, float x)
{
	data = glm::vec2(y, x);
}

Vector2::Vector2(bool random)
{
	if (random)
		randomizeVector();
	else
	{
		data = glm::vec2(0.0f, 0.0f);
	}
}

void Vector2::randomizeVector()
{
	srand((unsigned int) time(0));
	int v = rand() % 3;
	switch (v)
	{
	case 0:
		data = glm::vec2(1.0f, 1.0f);
		break;
	case 1:
		data = glm::vec2(-1.0f, 1.0f);
		break;
	case 2:
		data = glm::vec2(1.0f, -1.0f);
		break;
	case 3:
		data = glm::vec2(-1.0f, -1.0f);
		break;
	}
}

double Vector2::distance(const Vector2& from, const Vector2& target)
{
	return sqrt(pow(target.data[0] - from.data[0], 2) + pow(target.data[1] - from.data[1], 2));
}

Vector2 Vector2::getDisplacementVector(Vector2 vec, int yBound, int xBound)
{
	srand((unsigned int)time(0));
	int yDisplacement = (rand() % (yBound - 1)) + 1;
	int xDisplacement = (rand() % (xBound - 1)) + 1;

	switch (rand() % 3)
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

	return Vector2(vec.data[0] + yDisplacement, vec.data[1] + xDisplacement);
}
