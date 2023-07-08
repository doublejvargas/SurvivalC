#include "GameObject.h"

GameObject::GameObject()
	: m_Pos(Vector2(0.0f, 0.0f))
{ }

GameObject::GameObject(const Vector2& position)
	: m_Pos(position)
{ }

