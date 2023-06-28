#include "TerrainTile.h"
#include <stdlib.h>
#include <time.h>

TerrainTile::TerrainTile(float perlinVal, Game* game, const Vector2& pos)
	: GameObject(game, pos)
{
	m_isRevealedOnMiniMap = false;

	// Depending the Perlin Value, the terrain tile is given a specific terrain type, which in turn determines which routine function will be called to set up the tile
	if (perlinVal <= -0.25f)
	{
		m_TerrainType = TerrainType::WATER;
		setHasStatObj(false);
	}
	else if (perlinVal < 0.25f)
	{
		m_TerrainType = TerrainType::GRASSLAND;
		grasslandSetup();
	}
	else
	{
		m_TerrainType = TerrainType::DESERT;
		desertSetup();
	}
}

// These two functions use random numbers to probabilistically define the landscape, populating it with tree, rock, bush and cactus objects
void TerrainTile::grasslandSetup()
{
	srand((unsigned int) time(0));
	int val = rand() % 20;
	setHasStatObj(false);

	switch (val)
	{
	case 0:
	case 1:
		m_StatObjType = BUSH;
		m_StatObj = nullptr; //TODO get constructor from BUSH class
		setHasStatObj(true);
		break;
	case 3:
	case 4:
		m_StatObjType = TREE;
		m_StatObj = nullptr; //TODO get constructor from TREE class
		setHasStatObj(true);
		break;
	case 5:
		m_StatObjType = ROCK;
		m_StatObj = nullptr; //TODO get constructor from ROCK class
		setHasStatObj(true);
		break;
	default:
		setHasStatObj(false);
	}
}

void TerrainTile::desertSetup()
{
	srand((unsigned int) time(0));
	int val = rand() % 20;
	setHasStatObj(false);

	switch (val)
	{
	case 0:
		m_StatObjType = BUSH;
		m_StatObj = nullptr; //TODO get constructor from BUSH class
		setHasStatObj(true);
		break;
	case 1:
	case 2:
		m_StatObjType = ROCK;
		m_StatObj = nullptr; //TODO get constructor from ROCK class
		setHasStatObj(true);
		break;
	default:
		setHasStatObj(false);
	}
}

