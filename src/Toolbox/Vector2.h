#pragma once
#include "glm/glm.hpp"

class Vector2
{
public:
	Vector2() : m_v0(0), m_v1(0) {}
	Vector2(float v0, float v1);
	Vector2(const Vector2& v)
		: m_v0(v.v0()), m_v1(v.v1()) {}

	double distance(const Vector2& target);
	Vector2 getDisplacementVector(int yBound, int xBound);
	//useful for turning in game coordinates (y, x) into opengl coordinates (x, y)
	Vector2 reverse();

	inline float v0() const { return m_v0; }
	inline float v1() const { return m_v1; }

	static glm::vec2 to_glm_vec2(const Vector2 v);
	static glm::vec3 to_glm_vec3(const Vector2 v);

	friend bool operator==(const Vector2 V1, const Vector2 V2);

private:
	float m_v0;
	float m_v1;

};