#pragma once

class Vector2
{
public:
	Vector2() : m_v0(0), m_v1(0) {}
	Vector2(float v0, float v1);
	
	inline float v0() const	{ return m_v0; }
	inline float v1() const { return m_v1; }

	double distance(const Vector2& target);
	Vector2 getDisplacementVector(int yBound, int xBound);

	friend bool operator==(const Vector2 V1, const Vector2 V2);

private:
	float m_v0;
	float m_v1;

};