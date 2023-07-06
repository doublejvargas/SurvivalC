#pragma once
#include "Vector2.h"

class Game;

// Base class from which StationaryObject and MobileObject derive
class GameObject
{
public:

	// Multiple constructors because GameObjects are created frequently
	GameObject();
	GameObject(const Vector2& position);

	// Getters and setters
	inline Vector2 getPosition() const					{ return m_Pos; }
	inline void setPosition(const Vector2& position)	{ m_Pos = position; }


private:
	Vector2 m_Pos;
};
