#pragma once

#include "StationaryObject.h"
#include <random>

class Bush : protected StationaryObject
{
private:
	unsigned int m_NumBerries = 0;
	bool m_hasBerries = false;

public:
	//Constructor - Bush objects have 1/3 chance of containing a berry
	Bush(Game* game, const Vector2& pos)
		: StationaryObject(game, pos, true)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 3);
		//range[-1, 2]
		m_NumBerries = dis(gen) - 1;
		if (m_NumBerries > 0)
			m_hasBerries = true;
	}

	//TODO: finish implementing
	void interact(const Player& player) override
	{
		if (m_NumBerries)
		{
			//player.getinventory.insertfood(food.foodtype.berries) need to be implemented.
		}	
		m_hasBerries = false;
		m_NumBerries = 0;
	}

	inline bool HasBerries() const { return m_hasBerries; }
};