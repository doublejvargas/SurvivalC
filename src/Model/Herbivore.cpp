#include "Herbivore.h"

Herbivore::Herbivore(Map* map, Vector2 pos, int speed, int maxHP, int damage, const std::vector<bool>& canWalk, Texture* gameTex, Texture* combatTex, HERBIVORE_TYPE type)
	: Animal(map, pos, speed, maxHP, damage, canWalk, gameTex, combatTex)
{
	m_Type = type;
	setFled(false);
}

bool Herbivore::combatLogic(MobileObject& target)
{
	return Flee();
}

