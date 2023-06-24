#include "StationaryObject.h"

StationaryObject::StationaryObject(Game* game, Vector2 pos, bool passable)
	: GameObject(game, pos), m_isPassable(passable)
{

}