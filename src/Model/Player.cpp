#include "Player.h"
#include "Game.h"
#include "Base.h"
#include "Tree.h"

#include <random>
#include <stdexcept>

Player::Player(Map* map, const Vector2 & pos, int maxHP, Game* game)
	: MobileObject(map, pos, 1, maxHP), m_Game(game)
{
	m_StepsToday = 0;
	m_NumSticks = 0;
	m_Tool = ToolType::HAND;
	m_CanRest = false;
	m_Hidden = false;
	m_Harvesting = false;
	m_Resting = false;
	m_CyclesSinceRest = 1;
	m_Inventory = new Inventory(m_MaxWeight);
	setFacing(Game::DOWN);
	m_DisplayRestPrompt = false;
	m_DisplayUpgradePrompt = false;
}

Player::~Player()
{
	delete m_Inventory;
}

void Player::Eat(Food::FoodType type)
{
	Food eaten = m_Inventory->RemoveFood(type);
	if (eaten.getFoodType() != Food::FOOD_NULL)
		heal(eaten.getHPValue());
}

bool Player::Flee()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);
	//range[0, 1]
	if (int success = dis(gen) % 2)
	{
		setFled(true);
		return true;
	}
	return false;
}

bool Player::Attack(MobileObject& target)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);
	//range[0, 1]
	if (int success = dis(gen) % 2)
	{
		switch (m_Tool)
		{
		case HAND:
			target.SufferHarm(1); break;
		case STAKE:
			target.SufferHarm(2); break;
		case ROCK:
			target.SufferHarm(3); break;
		case SPEAR:
			target.SufferHarm(4); break;
		default:
			printf("Using ill-defined weapon.\n");
		}
		return true;
	}
	return false;
}

//implement once GAME class is implemented
void Player::AttemptMove(TerrainTile* T)
{
	if (T == nullptr)
		return;

	//Checks to see if there is an animal in the space the player is attempting to move into.  If so, interact is called on that animal.
	for (Animal* a : m_Game->getAnimals())
	{
		Vector2 tPos = T->getPosition();
		Vector2 aPos = a->getPosition();
		Vector2 aPriorPos = a->getPriorLoc();
		if (tPos == aPos || tPos == aPriorPos)
		{
			m_DisplayUpgradePrompt = false;
			m_DisplayRestPrompt = false;
			//In the case of all animals, interact will set the game.currentCombatEncounter
			a->interact(*this);
			break;
		}
	}

	//Equivalent statement to "if animal not encountered" or if animal interacts outside of combat (does not occur)
	if (m_Game->getCurrentEncounter() == nullptr)
	{
		//set prior location to current location before changing current location
		setPriorLoc(Vector2(getPosition()));
		if (T->hasStatObj())
		{
			//since all stationaryObjects implement interact-able, interact can and should be called.
			T->getStatObj()->interact(*this);
			if (T->getStatObjType() == TerrainTile::TREE || T->getStatObjType() == TerrainTile::BUSH)
			{
				m_Harvesting = true;
				T->setHasStatObj(false); //note: this also nulls the statobj pointer and changes enum type to null
			}
			//If no stationaryObject is present on TerrainTile t, the player moves into that tile, their steps increase,
			// and they are considered unhidden (had their been a rock in the space the player would automatically) be
			// set hidden when calling interact on the rock.  Setting hidden false here guarantees that when a player
			// leaves a grid square in which they are hidden they are revealed by default.
			else
			{
				setPosition(T->getPosition());
				takeStep();
				m_Hidden = false;
			}
			// checkForBase checks to see if the player is adjacent to their base
			m_DisplayUpgradePrompt = checkForBase();
			//If the player is near a rest-able object, and they haven't rested in at least 1 full cycle they can rest. also sets "canRest"
			m_DisplayRestPrompt = checkForRestable();
		}
	}

}

void Player::AttemptRest()
{
	if (m_CanRest)
	{
		m_CanRest = false;
		m_DisplayRestPrompt = false;
		m_DisplayUpgradePrompt = false;
		m_Resting = true;
		m_Game->clearAllAnimals();

		if (Base* base = dynamic_cast<Base*>(m_CurrentRestObject)) //TODO verify this works correctly
			base->restAt(*this, m_Game->getLoader());
		else if (Tree* tree = dynamic_cast<Tree*>(m_CurrentRestObject)) //TODO verify this works correctly
			tree->restAt(*this, m_Game->getLoader());
	}
}

void Player::upgradeTool()
{
	switch (m_Tool)
	{
	case HAND:	m_Tool = STAKE; break;
	case STAKE: m_Tool = ROCK;	break;
	case ROCK:	m_Tool = SPEAR;	break;
	case SPEAR:					break;
	default:
		fprintf(stderr, "%s", "Weapon is not upgradeable!\n");
	}
}

bool Player::spendSticks(int toSpend)
{
	if (getSticks() - toSpend >= 0)
	{
		m_NumSticks -= toSpend;
		return true;
	}
	return false;
}

void Player::gatherSticks(int sticksHarvested)
{
	m_NumSticks += sticksHarvested;
}

void Player::heal(int HP)
{
	int currentHP = getCurrentHP() + HP;
	setCurrentHP(currentHP > getMaxHP() ? getMaxHP() : currentHP);
}

void Player::takeStep()
{
	m_StepsToday++;
}

//TODO
bool Player::checkForRestable()
{
	uint32_t x = (uint32_t)getPosition().v1();
	uint32_t y = (uint32_t)getPosition().v0();
	auto tMap = getMap()->getTerrainTiles();

	for (uint32_t j = y - 1; j < y + 2; j++)
	{
		for (uint32_t i = x - 1; i < x + 2; i++)
		{
			try
			{
				TerrainTile t = tMap.at(j).at(i);
				//In this game, only trees and bases are IRestable objects.
				bool isRestable = (t.getStatObjType() == TerrainTile::StatObjType::BASE || t.getStatObjType() == TerrainTile::StatObjType::TREE);
				if (t.hasStatObj() && isRestable)
				{
					StationaryObject* so = t.getStatObj(); //TODO verify this works correctly
					m_CurrentRestObject = so;
					if (m_CyclesSinceRest >= 2)
					{
						m_CanRest = true;
						return true;
					}
				}
			}
			catch (const std::out_of_range& oor)
			{
				fprintf(stderr, "%s" " Tile range is out of the map! Obvs not a base! ;)\n", oor.what());
			}
		}
	}

	return false;
}

//TODO
bool Player::checkForBase()
{
	uint32_t x = (uint32_t)getPosition().v1();
	uint32_t y = (uint32_t)getPosition().v0();
	auto tMap = getMap()->getTerrainTiles();

	for (uint32_t j = y - 1; j < y + 2; j++)
	{
		for (uint32_t i = x - 1; i < x + 2; i++)
		{
			try
			{
				TerrainTile t = tMap.at(j).at(i);
				if (t.hasStatObj() && t.getStatObjType() == TerrainTile::StatObjType::BASE)
					return true;
			}
			catch (const std::out_of_range& oor)
			{
				fprintf(stderr, "%s" " Tile range is out of the map! Obvs not a base! ;)\n", oor.what());
			}
		}
	}

	return false;
}
