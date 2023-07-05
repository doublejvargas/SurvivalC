#pragma once

#include "StationaryObject.h"

class Rock : public StationaryObject
{
public:
	Rock(Game* game, const Vector2& pos)
		: StationaryObject(game, pos, true) { }

	//TODO: finish implementing
	void interact(const Player& player) override
	{
		//player.sethidden
		//player.setposition
		//player.takestep
	}
};
