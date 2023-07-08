#pragma once

#include "CombatEncounter.h"

class RestingCombatEncounter : public CombatEncounter
{
public:
	RestingCombatEncounter(Player* player, Animal* animal);

	void combatTurn() override;

private:
	void determineCombatOrder();
};
