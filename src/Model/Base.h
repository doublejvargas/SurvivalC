#pragma once

#include "StationaryObject.h"

typedef unsigned int uint32_t;

class Base : public StationaryObject, public Interfaces::IRestable
{
public:
	enum BaseStatus { CAMP, SHACK, HOUSE, FORT, NULLBASE };

	//Values representing the costs of upgrades, and the progression of the decreasing encounterChance.
	const uint32_t ENCOUNTER_CHANCES[4] = { 60, 50, 25, 10 };
	const uint32_t COST_UPGRADE_BASE[3] = { 50, 100, 150 };
	const uint32_t COST_UPGRADE_TOOL[3] = { 25, 50, 100 };

private:

	BaseStatus m_BaseStatus;
	uint32_t m_CurEncounterChance;
	uint32_t m_CurBaseCost;
	uint32_t m_CurToolCost;
	bool m_BeenUpgraded;

public:
	Base(Vector2 pos);

	void buyNewBaseUpgrade(Player& player);
	void upgradeBase();
	void buyNewToolUpgrade(Player& player);

	void interact(const Player& player) override;
	void restAt(const Player& player) override;

	// Getters
	inline uint32_t getCurToolCost() const { return m_CurToolCost; }
	inline uint32_t getCurBaseCost() const { return m_CurBaseCost; }
	inline BaseStatus getBaseStatus() const { return m_BaseStatus; }

	//Setters
	inline bool hasBeenUpgraded() const { return m_BeenUpgraded; }
	inline void setCurToolCost(uint32_t val) { m_CurToolCost = val; }
	inline void setBeenUpgraded(bool val) { m_BeenUpgraded = val; }

};