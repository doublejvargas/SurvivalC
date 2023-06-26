#pragma once
#include "Game.h"
#include "Vector2.h"

// Base class from which StationaryObject and MobileObject derive
class GameObject
{
public:

	// Multiple constructors because GameObjects are created frequently
	GameObject();
	GameObject(Game* game);
	GameObject(Game* game, const Vector2& position);

	// Getters and setters
	inline Game* getGame()								{ return m_Game; }
	inline Vector2 Position()							{ return m_Pos; }
	inline void setPosition(const Vector2& position)	{ m_Pos = position; }

	// Protected as derived classes will need to have access to these member variables
protected:
	// All objects in the game hold two important references: their position and a pointer to the game
	Game* m_Game;
	Vector2 m_Pos;
};
