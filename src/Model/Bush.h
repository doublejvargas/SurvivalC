#pragma once
#include "StationaryObject.h"
#include "Player.h"
#include "Food.h"
#include <random>

class Game;
class StationaryObject;

class Bush : public StationaryObject
{
private:
	uint32_t m_NumBerries = 0;
	bool m_hasBerries = false;

public:
	//Constructor - Bush objects have 1/3 chance of containing a berry
	Bush(const Vector2& pos)
		: StationaryObject(pos, true)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 3);
		//range[-1, 2]
		m_NumBerries = dis(gen) - 1;
		if (m_NumBerries > 0)
			m_hasBerries = true;
	}

	void interact(Player& player) override
	{
		if (m_NumBerries)
		{
			player.getInventory()->InsertFood(Food::Berries);
		}	
		m_hasBerries = false;
		m_NumBerries = 0;
	}

	inline bool HasBerries() const { return m_hasBerries; }
};