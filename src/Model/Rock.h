#pragma once

#include "StationaryObject.h"
#include "Player.h"

class Rock : public StationaryObject
{
public:
	Rock(const Vector2& pos)
		: StationaryObject(pos, true) { }

	void interact(Player& player) override
	{
		player.setHidden(true);
		player.setPosition(getPosition());
		player.takeStep();
	}
};
