#include "RestingCombatEncounter.h"
#include "Game.h"
#include "Player.h"
#include <random>

RestingCombatEncounter::RestingCombatEncounter(Player* player, Animal* animal)
	: CombatEncounter(player, animal) {}

void RestingCombatEncounter::combatTurn()
{
	CombatEncounter::combatTurn();
	if (isEncounterOver())
	{
		if (m_Player->isAlive() && !m_Player->isFled())
		{
			m_Player->heal(m_Player->getMaxHP());
			m_Player->setCyclesSinceRest(0);
			m_Player->setStepsToday(Game::STEPS_PER_CYCLE + 1);
			m_Player->getGame()->checkDayCycle();
		}
		if (!getAnimal()->isAlive())
		{
			setMessage("You slay the animal\n and get some much needed rest.");
			setDisplayMessage(true);
		}
		if (m_Player->isFled())
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, Game::HEIGHT > Game::WIDTH ? Game::HEIGHT : Game::WIDTH);
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

			setMessage("You flee into the wilderness!");
			setDisplayMessage(true);
		}
		//m_Player->getGame()->setCurrentEncounter(nullptr); //TODO finish game, then finish this
	}
}

void RestingCombatEncounter::determineCombatOrder()
{
	CombatEncounter::determineCombatOrder();	// This derived class has access to private routine because it also is a friend class
}

