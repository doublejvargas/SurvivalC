#pragma once
#include "glm/glm.hpp"


class Vector2
{
public:
	Vector2(float y, float x);
	Vector2(bool random);

	glm::vec2 data = glm::vec2(0, 0);

	static double distance(const Vector2& from, const Vector2& target);
	static Vector2 getDisplacementVector(Vector2 vec, int yBound, int xBound);

private:
	void randomizeVector();


};