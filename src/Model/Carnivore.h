#pragma once

#include "Animal.h"
#include "Map.h"

typedef unsigned int uint32_t;

class Player;

class Carnivore : public Animal
{
public:
	enum CARNIVORE_TYPE { WOLF, LION, CROCODILE, NULLCARNIVORE };
	const uint32_t VIEW_DISTANCE = 7;

private:
	CARNIVORE_TYPE m_Type = NULLCARNIVORE;

public:
	Carnivore(Map* map, Vector2 pos, int speed, int maxHP, int damage, const std::vector<bool>& canWalk, Texture* gameTex, Texture* combatTex, CARNIVORE_TYPE type);

	bool combatLogic(MobileObject& target) override;
	
private:
	//Private routines
	void chooseNewPosition(const Player& player) override;
	bool scanForPlayer(const Player& player, TerrainTile::TerrainType terrain);
	bool canWalk(TerrainTile::TerrainType terrain);

	//Getter
	inline CARNIVORE_TYPE getType() const { return m_Type; }
};
