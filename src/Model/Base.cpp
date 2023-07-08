#include "Base.h"
#include "Player.h"
#include "CarnivoreFactory.h"
#include "RestingCombatEncounter.h"
#include "Loader.h"
#include <random>


Base::Base(Vector2 pos)
	: StationaryObject(pos, false)
{
	m_BeenUpgraded = false;
	m_BaseStatus = BaseStatus::CAMP;
	m_CurEncounterChance = ENCOUNTER_CHANCES[0];
	m_CurBaseCost = COST_UPGRADE_BASE[0];
	m_CurToolCost = COST_UPGRADE_TOOL[0];
}

void Base::buyNewBaseUpgrade(Player& player)
{
	if (m_BaseStatus < BaseStatus::HOUSE)
	{
		if (player.spendSticks(m_CurBaseCost)) //access to private routine SpendSticks allowed because Base is a friend class.
			upgradeBase();
	}
}

void Base::upgradeBase()
{
	auto enumUpgrade = [](BaseStatus curStatus) -> BaseStatus
	{
		switch (curStatus)
		{
		case CAMP:	return SHACK;
		case SHACK:	return HOUSE;
		case HOUSE: return FORT;
		case FORT:	return FORT;
		
		default:
			return NULLBASE;
		}
	};
	
	m_BaseStatus = enumUpgrade(m_BaseStatus);
	m_CurEncounterChance = ENCOUNTER_CHANCES[(uint32_t)m_BaseStatus];

	uint32_t arrSize = sizeof(COST_UPGRADE_BASE) / sizeof(*COST_UPGRADE_BASE);

	if ((uint32_t)m_BaseStatus < arrSize) //TODO ensure this conditional works
	{
		m_CurBaseCost = COST_UPGRADE_BASE[(uint32_t)m_BaseStatus];
	}

	m_BeenUpgraded = true;
}

void Base::buyNewToolUpgrade(Player& player)
{
	if (player.getTool() < 3) //TODO ensure this comparison works
	{
		if (player.spendSticks(m_CurToolCost))
		{
			player.upgradeTool();
			uint32_t arrSize = sizeof(COST_UPGRADE_TOOL) / sizeof(*COST_UPGRADE_TOOL);
			if ((uint32_t)player.getTool() < arrSize) //TODO ensure this comparison works
				m_CurToolCost = COST_UPGRADE_TOOL[(uint32_t)player.getTool()];
		}
	}
}

void Base::interact(Player& player)
{
	// Empty function call.  This is implementation of the Interactable interface.  The reason it is here is that it
		//conveniently disables the player's ability to move into this space. If an interactable object can be walked
		//into or over, this method will manually set the player's location.  Since the location is not set in this
		//function, it serves to allow bases to exist as impassable terrain to the player.
}

void Base::restAt(Player& player, Loader* loader)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 101);

	uint32_t encounterRoll = dis(gen);
	Carnivore* enemy = nullptr;

	if (encounterRoll < m_CurEncounterChance)
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

		player.getGame()->setCurrentEncounter(new RestingCombatEncounter(&player, enemy)); //todo delete this somewhere? potential memory leak
	}
	else
	{
		player.heal(player.getMaxHP());
		player.setCyclesSinceRest(0);
	}
}

