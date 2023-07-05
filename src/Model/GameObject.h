#pragma once
#include "Vector2.h"

class Game;

// Base class from which StationaryObject and MobileObject derive
class GameObject
{
public:

	// Multiple constructors because GameObjects are created frequently
	GameObject();
	GameObject(Game* game);
	GameObject(Game* game, const Vector2& position);

	// Getters and setters
	inline Game* getGame() const						{ return m_Game; }
	inline Vector2 getPosition() const					{ return m_Pos; }
	inline void setPosition(const Vector2& position)	{ m_Pos = position; }
	inline void setGamePtr(Game* game)					{ m_Game = game; }


private:
	// All objects in the game hold two important references: their position and a pointer to the game (???) questionable as i develop this game.
	Game* m_Game = nullptr;
	Vector2 m_Pos;
};
