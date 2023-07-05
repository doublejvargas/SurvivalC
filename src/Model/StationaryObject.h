#pragma once

#include "GameObject.h"
#include "Interfaces.h"

// Stationary objects are a single step away from GameObject in the class hierarchy. They do not contain any methods
// which allow them to move, and contain only a small bit of new information. Whether or not they are passable by
// animal entities, and that they are guaranteed to implement the IInteractable interface.
class StationaryObject : public GameObject, public Interfaces::IInteractable
{
public:
	StationaryObject(Game* game, Vector2 pos, bool passable)
		: GameObject(game, pos), m_isPassable(passable) {}

	inline bool isPassable() const { return m_isPassable; }
	inline void setPassable(bool val) { m_isPassable = val; }

private:
	// Determines whether animals may walk through object
	bool m_isPassable;
};