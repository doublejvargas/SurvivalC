#include "CombatEncounter.h"
#include "Game.h"
#include "Player.h"
#include "Animal.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include <random>

// Local helper function
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

CombatEncounter::CombatEncounter(Player* player, Animal* animal)
{
	m_Player = player;
	m_Animal = animal;
	m_Player->getGame()->setAnimalTaggedForRemoval(true);
	m_Animal->setRemove(true);
	m_PlayerTurn = false;
	m_AnimalTurn = false;
	m_DisplayMessage = false;
	m_Animal->setFled(false);
	m_Player->setFled(false);
	m_EncounterOver = false;
	determineCombatOrder();
}

void CombatEncounter::combatTurn()
{
	if (!m_Player->isAlive() || !m_Animal->isAlive() || m_Player->isFled() || m_Animal->isFled())
		m_EncounterOver = true;

	if (!m_EncounterOver)
	{
		if (m_AnimalTurn && m_Animal->isAlive() && !m_Animal->isFled())
		{
			if (m_Animal->combatLogic(*m_Player))
			{
				if (dynamic_cast<Carnivore*>(m_Animal)) //TODO: verify this works properly
					m_Message = "The animal attacks viciously!\n It bites you!";
				else
					m_Message = "The animal attempts to flee!";
			}
			else
			{
				if (/*instanceof<Carnivore>(m_Animal)*/dynamic_cast<Carnivore*>(m_Animal)) //TODO: verify this works properly
					m_Message = "The animal attacks viciously!\n You dodge its attack!";
				else
					m_Message = "The animal attempts to flee!\n You stop it from escaping";
			}

			m_DisplayMessage = true;
			m_AnimalTurn = false;
			m_PlayerTurn = true;
		}
	}
	else
	{
		if (!m_Animal->isAlive())
		{
			m_Message = "You've slayed the animal!";
			decodeMeats();
		}
		else if (m_Animal->isFled())
			m_Message = "It gets away!";
		else if (m_Player->isFled())
		{
			if (/*instanceof<Carnivore>(m_Animal)*/dynamic_cast<Carnivore*>(m_Animal))//TODO: verify this works properly
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(0, Game::HEIGHT > Game::WIDTH ? (Game::HEIGHT-1) : (Game::WIDTH-1));
				Map* map = m_Player->getMap();
				size_t y = 0;
				size_t x = 0;
				do 
				{
					m_Player->setPosition(Vector2((float)dis(gen), (float)dis(gen)));
					y = (size_t)m_Player->getPosition().v0();
					x = (size_t)m_Player->getPosition().v1();
				} while (map->getTerrainTiles().at(y).at(x).getTerrainType() != TerrainTile::GRASSLAND ||
							map->getTerrainTiles().at(y).at(x).hasStatObj());//TODO: verify this works properly

				m_Message = "You flee into the wilderness!";
			}
			else
			{
				if (/*instanceof<Herbivore>(m_Animal)*/Herbivore* herb = dynamic_cast<Herbivore*>(m_Animal))//TODO: verify this works properly
				{
					if (herb && herb->getType() != Herbivore::FISH)
						m_Message = "You let the animal scamper off.";
					else
						m_Message = "You let the fish swim off.";
				}
			}
		}
	}
	if (!m_Player->isAlive())
		m_Message = "You've been mortally wounded. \nYou didn't survive.";
	
	m_DisplayMessage = true;
}

void CombatEncounter::determineCombatOrder()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 2);
	int encounterOrder = dis(gen);
	
	switch (encounterOrder)
	{
	case 0:
		m_PlayerTurn = true;
		m_Message = "You seize the initiative!";
		break;
	default:
		m_AnimalTurn = true;
		m_Message = "The animal moves quickly!";
	}

	m_DisplayMessage = true;
}

void CombatEncounter::decodeMeats()
{
	if (Carnivore *carn = dynamic_cast<Carnivore*>(m_Animal))//TODO: verify this works correctly
	{
		switch (carn->getType())
		{
		case Carnivore::LION:
			m_Player->getInventory()->InsertFood(Food::Lion);
			break;
		case Carnivore::WOLF:
			m_Player->getInventory()->InsertFood(Food::Wolf);
			break;
		case Carnivore::CROCODILE:
			m_Player->getInventory()->InsertFood(Food::Crocodile);
			break;
		}
	}
	else if (Herbivore* herb = dynamic_cast<Herbivore*>(m_Animal))//TODO: verify this works correctly
	{
		switch (herb->getType())
		{
		case Herbivore::RABBIT:
			m_Player->getInventory()->InsertFood(Food::Rabbit);
			break;
		case Herbivore::DEER:
			m_Player->getInventory()->InsertFood(Food::Deer);
			break;
		case Herbivore::FISH:
			m_Player->getInventory()->InsertFood(Food::Fish);
			break;
		}
	}
}
