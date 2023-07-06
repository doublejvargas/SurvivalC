#include "Game.h"
#include <random>

Game::Game(Loader* loader) 
{
	m_GameWon = false;
	m_GameOver = false;
	m_DayTime = true;
	m_InCombat = false;
	m_AnimalTaggedForRemoval = false;
	m_Day = 1;

	m_Loader = loader;
	m_Map = new Map(loader);
	
	placePlayerAndBase();
	initMapReveal();
}

void Game::checkForEncounter()
{
	if (m_Animals.size() < MAX_ANIMALS)
	{
		Vector2 priorLoc = m_Player->getPriorLoc();
		Vector2 pos = m_Player->getPosition();
		if (!(priorLoc == pos))
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, 40);
			uint32_t encounter = dis(gen);
			
			switch (encounter)
			{
				case 0:
					spawnNewHerbivore(); break;
				case 1:
					spawnNewCarnivore(); break;
			}
		}
	}
}

void Game::spawnNewHerbivore()
{
	// implement when factories are implemented //TODO
}

void Game::spawnNewCarnivore()
{
	// implement when factories are implemented //TODO
}

Vector2 Game::spawnNewAnimalLocation()
{
	switch (DOWN/*m_Player->getFacing()*/) //TODO
	{
	case UP:
		return Vector2(m_Player->getPosition().v0() - 11, m_Player->getPosition().v1() - 11);
	case DOWN:
		return Vector2(m_Player->getPosition().v0() + 11, m_Player->getPosition().v1());
	case RIGHT:
		return Vector2(m_Player->getPosition().v0(), m_Player->getPosition().v1() + 11);
	default:
		return Vector2(m_Player->getPosition().v0(), m_Player->getPosition().v1() - 11);
	}
}

void Game::despawnDistantAnimals()
{
	for (Animal* animal : m_Animals)
	{
		if (animal->getPosition().distance(m_Player->getPosition()) > 20)
		{
			animal->setRemove(true);
			m_AnimalTaggedForRemoval = true;
		}
	}
}

void Game::clearAllAnimals()
{
	for (Animal* animal : m_Animals)
		animal->setRemove(true);

	m_AnimalTaggedForRemoval = true;
}

void Game::checkDayCycle()
{
	if (m_Player->getStepsToday() > STEPS_PER_CYCLE)
	{
		m_DayTime = !m_DayTime;
		m_Player->setStepsToday(0);
		m_Player->setCyclesSinceRest(m_Player->getCyclesSinceRest() + 1);
		
		if (m_Player->getCyclesSinceRest() > 2)
			m_Player->SufferHarm(m_Player->getCyclesSinceRest());
		else if (m_Player->getCyclesSinceRest() > 1)
			m_Player->SufferHarm(1);

		if (m_DayTime)
			m_Day++;
	}
}

void Game::mapRevealAfterFlee()
{
	initMapReveal();
	m_Player->setFled(false);
}

void Game::placePlayerAndBase()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, WIDTH <= HEIGHT ? WIDTH : HEIGHT);

	m_Player = new Player(m_Map, Vector2(0, 0), 10);
	uint32_t y = dis(gen); //random
	uint32_t x = dis(gen); // random
	TerrainTile::TerrainType T = m_Map->GetTerrainTiles().at(0).at(0).getTerrainType();
	bool hasObj = false;
	do 
	{
		m_Player->setPosition(Vector2((float)y, (float)x));
		T = m_Map->GetTerrainTiles().at(y).at(x).getTerrainType();
		hasObj = m_Map->GetTerrainTiles().at(y).at(x).hasStatObj();
	} while (T != TerrainTile::GRASSLAND /*|| !hasObj*/); //TODO reenable that conditional once i produce objects on map

	Vector2 displacementVector;
	bool basePlaced = false;

	do 
	{
		displacementVector = m_Player->getPosition().getDisplacementVector(2, 2);
		try
		{
			if (m_Map->GetTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).getTerrainType() != TerrainTile::WATER)
			{
				m_Map->GetTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setHasStatObj(false);
				m_Map->GetTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setHasStatObj(true);
				m_Map->GetTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setStatObjType(TerrainTile::BASE);
				// initialize base here
				m_Map->GetTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setStatObj(nullptr /*base*/);
				basePlaced = true;
			}
		}
		catch (const std::out_of_range& e)
		{
			// if out of bounds, do nothing
			fprintf(stderr, "oor coords to place base! but no worries. pos: (%d, %d). err: %s\n", y, x, e.what());
		}
		
	} while (!basePlaced);

	clearBrush();
}

void Game::clearBrush()
{
	uint32_t y = 0; /*(uint32_t)m_Base.getPosition().v0()*/; //todo
	uint32_t x = 0; /*(uint32_t)m_Base.getPosition().v1()*/; //todo

	for (uint32_t j = y - 2; j < y + 3; j++)
	{
		for (uint32_t i = x - 2; i < x + 3; i++)
		{
			if (j != y || i != x)
			{
				try
				{
					//set Tile's Stationary Object to null. Set Tile's hasStatObj flag to false
					m_Map->GetTerrainTiles().at(j).at(i).setHasStatObj(false);
				}
				catch (const std::out_of_range& e)
				{
					//Ignore exception.  Signifies base is near edge of map
					fprintf(stderr, "base near edge of map! but no worries. pos: (%d, %d). err: %s\n", y, x, e.what());
				}
			}
		}
	}
}

void Game::initMapReveal()
{
	uint32_t y = (uint32_t)m_Player->getPosition().v0();
	for (uint32_t y = (uint32_t)m_Player->getPosition().v0() - 10; y <= m_Player->getPosition().v0() + 10; y++)
	{
		for (uint32_t x = (uint32_t)m_Player->getPosition().v1() - 10; x <= m_Player->getPosition().v1() + 10; x++)
		{
			try
			{
				m_Map->GetTerrainTiles().at(y).at(x).setIsRevealedOnMiniMap(true);
			}
			catch (const std::out_of_range& e)
			{
				// do nothing, it just means there is no map to reveal there
				fprintf(stderr, "no map to reveal here! but no worries. pos: (%d, %d). err: %s\n", y, x, e.what());
			}
		}
	}
}
