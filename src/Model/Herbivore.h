#pragma once

#include "Animal.h"

class Herbivore : public Animal 
{
public:
	enum HERBIVORE_TYPE { RABBIT, FISH, DEER, NULLHERBIVORE };
	
private:
	HERBIVORE_TYPE m_Type = NULLHERBIVORE;

public:
	Herbivore(Map* map, Vector2 pos, int speed, int maxHP, int damage, const std::vector<bool>& canWalk, Texture* gameTex, Texture* combatTex, HERBIVORE_TYPE type);

	bool combatLogic(MobileObject& target) override;

	inline HERBIVORE_TYPE getType() const { return m_Type; }
};