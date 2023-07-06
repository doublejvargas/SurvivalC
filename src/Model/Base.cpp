#include "Base.h"
#include "Player.h"
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
		if (player.SpendSticks(m_CurBaseCost)) //access to private routine SpendSticks allowed because Base is a friend class.
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
		if (player.SpendSticks(m_CurToolCost))
		{
			player.UpgradeTool();
			uint32_t arrSize = sizeof(COST_UPGRADE_TOOL) / sizeof(*COST_UPGRADE_TOOL);
			if ((uint32_t)player.getTool() < arrSize) //TODO ensure this comparison works
				m_CurToolCost = COST_UPGRADE_TOOL[(uint32_t)player.getTool()];
		}
	}
}

void Base::interact(const Player& player)
{
	// Empty function call.  This is implementation of the Interactable interface.  The reason it is here is that it
		//conveniently disables the player's ability to move into this space. If an interactable object can be walked
		//into or over, this method will manually set the player's location.  Since the location is not set in this
		//function, it serves to allow bases to exist as impassable terrain to the player.
}

void Base::restAt(const Player& player)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 101);

	uint32_t encounterRoll = dis(gen);

	if (encounterRoll < m_CurEncounterChance)
	{
		// TODO: complete once factories are implemented
	}
}

