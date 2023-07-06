#pragma once

#include "StationaryObject.h"

class Rock : public StationaryObject
{
public:
	Rock(const Vector2& pos)
		: StationaryObject(pos, true) { }

	//TODO: finish implementing
	void interact(const Player& player) override
	{
		//player.sethidden
		//player.setposition
		//player.takestep
	}
};
