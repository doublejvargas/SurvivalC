#include "TerrainTile.h"
#include "Bush.h"
#include "Tree.h"
#include "Rock.h"
#include <stdlib.h>
#include <time.h>
#include <random>

TerrainTile::TerrainTile(float perlinVal, const Vector2& pos)
	: GameObject(pos)
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

//TerrainTile::~TerrainTile()
//{
//	printf("calling terraintile destructor!\n");
//	if (m_StatObj)
//		delete m_StatObj;
//}

// These two functions use random numbers to probabilistically define the landscape, populating it with tree, rock, bush and cactus objects
void TerrainTile::grasslandSetup()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 40);

	setHasStatObj(false);

	switch (dis(gen))
	{
	case 0:
		break;
	case 1:
		m_StatObjType = BUSH;
		m_StatObj = new Bush(getPosition()); //delete in destructor?
		setHasStatObj(true);
		break;
	case 3:
		break;
	case 4:
		m_StatObjType = TREE;
		m_StatObj = new Tree(getPosition()); //delete in destructor
		setHasStatObj(true);
		break;
	case 5:
		m_StatObjType = ROCK;
		m_StatObj = new Rock(getPosition()); //delete in destructor
		setHasStatObj(true);
		break;
	default:
		setHasStatObj(false);
	}
}

void TerrainTile::desertSetup()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 50);
	setHasStatObj(false);

	switch (dis(gen))
	{
	case 0:
		m_StatObjType = BUSH;
		m_StatObj = new Bush(getPosition()); //delete in destructor ?
		setHasStatObj(true);
		break;
	case 1:
		break;
	case 2:
		m_StatObjType = ROCK;
		m_StatObj = new Rock(getPosition()); //delete in destructor ?
		setHasStatObj(true);
		break;
	default:
		setHasStatObj(false);
	}
}

