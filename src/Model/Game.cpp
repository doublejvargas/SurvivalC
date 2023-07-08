#include "Game.h"
#include "Player.h"
#include "Base.h"
#include "CarnivoreFactory.h"
#include "HerbivoreFactory.h"
#include "CombatEncounter.h"
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
	m_Map = new Map(loader); //delete in destructor!
	
	// These two functions cause some errors that seem to be out of bound reference or dereferencing uninitialized values
	placePlayerAndBase(); //initializes m_Base and m_Player
	initMapReveal();
}

Game::~Game()
{
	delete m_Map;
	delete m_Base;
	delete m_Player;
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
	try
	{
		Vector2 newPos = spawnNewAnimalLocation();
		uint32_t y = (uint32_t)newPos.v0();
		uint32_t x = (uint32_t)newPos.v1();
		if (m_Map->getTerrainTiles().at(y).at(x).getTerrainType() != TerrainTile::WATER)
		{
			if (m_Map->getTerrainTiles().at(y).at(x).getTerrainType() != TerrainTile::DESERT)
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(0, 2);
				bool rabbit = dis(gen); //0 or 1
				if (rabbit)
					m_Animals.push_back(HerbivoreFactory::ProduceHerbivore(m_Map, newPos, Herbivore::RABBIT, m_Loader));
				else
					m_Animals.push_back(HerbivoreFactory::ProduceHerbivore(m_Map, newPos, Herbivore::DEER, m_Loader));
			}
			else
				m_Animals.push_back(HerbivoreFactory::ProduceHerbivore(m_Map, newPos, Herbivore::RABBIT, m_Loader));
		}
		else
			m_Animals.push_back(HerbivoreFactory::ProduceHerbivore(m_Map, newPos, Herbivore::FISH, m_Loader));
	}
	catch (const std::out_of_range& oor)
	{
		fprintf(stderr, "%s" " New position is out of bounds! cannot spawn herbivore there.\n", oor.what());
	}
}

void Game::spawnNewCarnivore()
{
	try
	{
		Vector2 newPos = spawnNewAnimalLocation();
		uint32_t y = (uint32_t)newPos.v0();
		uint32_t x = (uint32_t)newPos.v1();
		if (m_Map->getTerrainTiles().at(y).at(x).getTerrainType() != TerrainTile::WATER)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, 2);
			bool wolf = dis(gen); //0 or 1
			if (wolf)
				m_Animals.push_back(CarnivoreFactory::ProduceCarnivore(m_Map, newPos, Carnivore::WOLF, m_Loader));
			else
				m_Animals.push_back(CarnivoreFactory::ProduceCarnivore(m_Map, newPos, Carnivore::LION, m_Loader));		
		}
		else
			m_Animals.push_back(CarnivoreFactory::ProduceCarnivore(m_Map, newPos, Carnivore::CROCODILE, m_Loader));
	}
	catch (const std::out_of_range& oor)
	{
		fprintf(stderr, "%s" " New position is out of bounds! cannot spawn carnivore there.\n", oor.what());
	}
}

Vector2 Game::spawnNewAnimalLocation()
{
	switch (m_Player->getFacing())
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
	std::uniform_int_distribution<> dis(0, WIDTH <= HEIGHT ? WIDTH : HEIGHT); //bound to the lesser value
	uint32_t y = 0; //random
	uint32_t x = 0; // random
	m_Player = new Player(m_Map, Vector2(0, 0), 10, this); //delete in destructor!
 
	TerrainTile::TerrainType terrain = m_Map->getTerrainTiles().at(0).at(0).getTerrainType();
	bool hasObj = false;
	do 
	{
		try 
		{
			y = dis(gen); //random
			x = dis(gen); //random
			m_Player->setPosition(Vector2((float)y, (float)x));
			terrain = m_Map->getTerrainTiles().at(y).at(x).getTerrainType();
			hasObj = m_Map->getTerrainTiles().at(y).at(x).hasStatObj();
		}
		catch (const std::out_of_range& e)
		{
			fprintf(stderr, "placing player exception, not sure what this err is. pos: (%d, %d). err: %s\n", y, x, e.what());
		}
		
	} while (terrain != TerrainTile::GRASSLAND || hasObj); //repeat while terrain type is not grassland OR it has an object. ie. stop when either it is grass or doesn't have obj
	
	Vector2 displacementVector;
	bool basePlaced = false;
	do 
	{
		displacementVector = m_Player->getPosition().getDisplacementVector(2, 2);
		try
		{
			if (m_Map->getTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).getTerrainType() != TerrainTile::WATER)
			{
				m_Map->getTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setHasStatObj(false);
				m_Map->getTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setHasStatObj(true);
				m_Map->getTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setStatObjType(TerrainTile::BASE);
				// initialize base here
				m_Base = new Base(displacementVector); //DELETE in destructor!
				m_Map->getTerrainTiles().at((size_t)displacementVector.v0()).at((size_t)displacementVector.v1()).setStatObj(/*(StationaryObject* )*/m_Base); //TODO verify this isn't an issue
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
	uint32_t y = (uint32_t)m_Base->getPosition().v0();
	uint32_t x = (uint32_t)m_Base->getPosition().v1();

	for (uint32_t j = y - 2; j < y + 3; j++)
	{
		for (uint32_t i = x - 2; i < x + 3; i++)
		{
			if (j != y || i != x)
			{
				try
				{
					//set Tile's Stationary Object to null. Set Tile's hasStatObj flag to false
					m_Map->getTerrainTiles().at(j).at(i).setHasStatObj(false);
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
	/*uint32_t y = (uint32_t)m_Player->getPosition().v0();*/
	for (uint32_t y = (uint32_t)m_Player->getPosition().v0() - 10; y <= m_Player->getPosition().v0() + 10; y++)
	{
		for (uint32_t x = (uint32_t)m_Player->getPosition().v1() - 10; x <= m_Player->getPosition().v1() + 10; x++)
		{
			try
			{
				m_Map->getTerrainTiles().at(y).at(x).setIsRevealedOnMiniMap(true);
			}
			catch (const std::out_of_range& e)
			{
				// do nothing, it just means there is no map to reveal there
				fprintf(stderr, "no map to reveal here! but no worries. pos: (%d, %d). err: %s\n", y, x, e.what());
			}
		}
	}
}
