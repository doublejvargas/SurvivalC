#include "Player.h"
#include "Game.h"
#include <random>
#include <stdexcept>

Player::Player(Map* map, const Vector2 & pos, int maxHP)
	:MobileObject(map, pos, 1, maxHP)
{
	m_StepsToday = 0;
	m_NumSticks = 0;
	m_Tool = ToolType::HAND;
	m_CanRest = false;
	m_Hidden = false;
	m_Harvesting = false;
	m_Resting = false;
	m_CyclesSinceRest = 1;
	m_Inventory = Inventory(m_MaxWeight);
	//setFacing(Game.Direction.DOWN); //TODO
	m_DisplayRestPrompt = false;
	m_DisplayUpgradePrompt = false;
}

void Player::Eat(Food::FoodType type)
{
	Food eaten = m_Inventory.RemoveFood(type);
	if (eaten.getFoodType() != Food::FoodType::FOOD_NULL)
		Heal(eaten.getHPValue());
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
}

void Player::AttemptRest(Game* game)
{
	if (m_CanRest)
	{
		m_CanRest = false;
		m_DisplayRestPrompt = false;
		m_DisplayUpgradePrompt = false;
		m_Resting = true;
		game->clearAllAnimals();
		//m_CurrentRestObject.restAt(this); //TODO
	}
}

void Player::UpgradeTool()
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

bool Player::SpendSticks(int toSpend)
{
	if (getSticks() - toSpend >= 0)
	{
		m_NumSticks -= toSpend;
		return true;
	}
	return false;
}

void Player::GatherSticks(int sticksHarvested)
{
	m_NumSticks += sticksHarvested;
}

void Player::Heal(int HP)
{
	int currentHP = getCurrentHP() + HP;
	setCurrentHP(currentHP > getMaxHP() ? getMaxHP() : currentHP);
}

void Player::TakeStep()
{
	m_StepsToday++;
}

//TODO
bool Player::CheckForRestable()
{
	int x = (int)getPosition().v1();
	int y = (int)getPosition().v0();
	//auto tMap = getGame().getMap().getTerrainMap();

	//for (uint32_t j = y - 1; j < y + 2; j++)
	//{
	//	for (uint32_t i = x - 1; i < x + 2; i++)
	//	{
	//		try
	//		{
	//			TerrainTile t = tMap[j][i];
	//			//In this game, only trees and bases are IRestable objects.
	//			bool isRestable = (t.getStatObjType() == TerrainTile::StatObjType::BASE || t.getStatObjType() == TerrainTile::StatObjType::TREE);
	//			if (t.hasStatObj() && isRestable)
	//			{
	//				GameObject* so = (GameObject*)t.getStatObj();
	//				m_CurrentRestObject = *so;
	//				if (m_CyclesSinceRest >= 2)
	//				{
	//					m_CanRest = true;
	//					return true;
	//				}
	//			}
	//		}
	//		catch (const std::out_of_range& oor)
	//		{
	//			fprintf(stderr, "%s", "Tile range is out of the map! Obvs not a base! ;)\n");
	//		}
	//	}
	//}

	return false;
}

//TODO
bool Player::CheckForBase()
{
	int x = (int)getPosition().v1();
	int y = (int)getPosition().v0();
	//auto tMap = getGame().getMap().getTerrainMap();

	/*for (uint32_t j = y - 1; j < y + 2; j++)
	{
		for (uint32_t i = x - 1; i < x + 2; i++)
		{
			try
			{
				TerrainTile t = tMap[j][i];
				if (t.hasStatObj() && t.getStatObjType() == TerrainTile::StatObjType::BASE)
					return true;
			}
			catch (const std::out_of_range& oor)
			{
				fprintf(stderr, "%s", "Tile range is out of the map! Obvs not a base! ;)\n");
			}
		}
	}*/

	return false;
}
