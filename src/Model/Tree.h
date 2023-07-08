#pragma once

#include "StationaryObject.h"
#include "CarnivoreFactory.h"
#include "RestingCombatEncounter.h"
#include <random>

class Tree : public StationaryObject, public Interfaces::IRestable
{
private:
	uint32_t m_numSticks = 0;
	const uint32_t ENCOUNTER_CHANCE = 65;

public:
	Tree(const Vector2& pos)
		: StationaryObject(pos, true)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 3);
		//range[1,4]
		m_numSticks = dis(gen) + 1; 
	}

	void interact(Player& player) override
	{
		player.gatherSticks(m_numSticks);
		m_numSticks = 0;
	}

	void restAt(Player& player, Loader* loader) override
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 101);

		uint32_t encounterRoll = dis(gen);
		Carnivore* enemy = nullptr;

		if (encounterRoll < ENCOUNTER_CHANCE)
		{
			int enemyType = dis(gen) % 3;
			if (enemyType == 1)
			{
				enemy = CarnivoreFactory::ProduceCarnivore(player.getMap(), Vector2(0.0f, 0.0f), Carnivore::WOLF, loader);
			}
			else if (enemyType == 2)
			{
				enemy = CarnivoreFactory::ProduceCarnivore(player.getMap(), Vector2(0.0f, 0.0f), Carnivore::LION, loader);
			}

			player.getGame()->setCurrentEncounter(new RestingCombatEncounter(&player, enemy)); //todo delete in destructor!? potential memory leak
		}
		else
		{
			player.heal(player.getMaxHP());
			player.setCyclesSinceRest(0);
		}


	}
};