#pragma once

class Vector2
{
public:
	Vector2(float v0, float v1);
	Vector2(bool random);
	Vector2(const Vector2& v);

	inline float v0() const{ return m_v0; }
	inline float v1() const { return m_v1; }

	static double distance(const Vector2& from, const Vector2& target);
	static Vector2 getDisplacementVector(Vector2 vec, int yBound, int xBound);

private:
	void randomizeVector();
	float m_v0;
	float m_v1;

};