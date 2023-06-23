#include "GameObject.h"

GameObject::GameObject()
	: m_Game(nullptr), m_Pos(Vector2(0.0f, 0.0f))
{ }

GameObject::GameObject(Game* game)
	: m_Game(game), m_Pos(Vector2(0.0f, 0.0f))
{ }

GameObject::GameObject(Game* game, const Vector2& position)
	: m_Game(game), m_Pos(position)
{ }

