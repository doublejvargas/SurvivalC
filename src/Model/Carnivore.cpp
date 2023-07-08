#include "Carnivore.h"
#include "Player.h"

Carnivore::Carnivore(Map* map, Vector2 pos, int speed, int maxHP, int damage, const std::vector<bool>& canWalk, Texture* gameTex, Texture* combatTex, CARNIVORE_TYPE type)
	: Animal(map, pos, speed, maxHP, damage, canWalk, gameTex, combatTex)
{
	m_Type = type;
	setFled(false);
}

bool Carnivore::combatLogic(MobileObject & target)
{
	return Attack(target);
}

void Carnivore::chooseNewPosition(const Player& player)
{

	Vector2 playerPos = player.getPosition();
	TerrainTile::TerrainType terrain = getMap()->getTerrainTiles().at((size_t)playerPos.v0()).at((size_t)playerPos.v1()).getTerrainType();
	if (scanForPlayer(player, terrain))
		setTargetPos(playerPos);
	else
		Animal::chooseNewPosition(player);
}

bool Carnivore::scanForPlayer(const Player& player, TerrainTile::TerrainType terrain)
{
	return (getPosition().distance(player.getPosition()) <= VIEW_DISTANCE && !player.isHidden() && canWalk(terrain));
}

bool Carnivore::canWalk(TerrainTile::TerrainType terrain)
{
	switch (terrain)
	{
	case TerrainTile::WATER:
		return canWalkWater();
	case TerrainTile::GRASSLAND:
		return canWalkGrass();
	case TerrainTile::DESERT:
		return canWalkDesert();
	default:
		return false;
	}
}

// Carnivore& Carnivore::operator=(const Carnivore& c)
// {
// 	m_Type = c.getType();
// }

