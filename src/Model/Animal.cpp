#include "Animal.h"
#include "TerrainTile.h"
#include "Player.h"
#include "StationaryObject.h"
#include <random>

Animal::Animal(Game* game, const Vector2& pos, uint32_t speed, uint32_t maxHP, uint32_t damage, std::vector<bool> canWalk, Texture* gameTex, Texture* combatTex)
	: MobileObject(game, pos, speed, maxHP)
{
	m_CanWalkGrass = canWalk[0];
	m_CanWalkDesert = canWalk[1];
	m_CanWalkWater = canWalk[2];
	m_GameTexture = gameTex;
	m_CombatTexture = combatTex;
	m_Damage = damage;
	m_PathCompleted = true;
	m_Remove = false;
	m_PathFinder = new AStarPathFinder(game, canWalk); // delete in destructor
}

Animal::~Animal()
{
	delete m_PathFinder;
}

void Animal::chooseNewPosition()
{
	Game* game = getGame();
	std::vector<std::vector<TerrainTile>> tMap; //game.getMap().getTerrainMap();
	bool pathChosen = false;
	uint32_t attempts = 0;

	do 
	{
		m_TargetPos = getPosition().getDisplacementVector(5, 5);
		uint32_t targetY = (uint32_t)m_TargetPos.v0();
		uint32_t targetX = (uint32_t)m_TargetPos.v1();
		if (targetY < 100 /*game.getWidth()*/ && targetX < 100 /*game.getwidth()*/ && targetY >= 0 && targetX >= 0)
		{
			if (m_CanWalkWater && tMap.at(targetY).at(targetX).getTerrainType() == TerrainTile::TerrainType::WATER)
				pathChosen = true;
			else if (m_CanWalkWater && tMap.at(targetY).at(targetX).getTerrainType() == TerrainTile::TerrainType::GRASSLAND)
			{
				if (tMap.at(targetY).at(targetX).hasStatObj())
				{
					if (tMap.at(targetY).at(targetX).getStatObj()->isPassable())
						pathChosen = true;
				}
				else
					pathChosen = true;
			}
			else if (m_CanWalkWater && tMap.at(targetY).at(targetX).getTerrainType() == TerrainTile::TerrainType::DESERT)
			{
				if (tMap.at(targetY).at(targetX).hasStatObj())
				{
					if (tMap.at(targetY).at(targetX).getStatObj()->isPassable())
						pathChosen = true;
				}
				else
					pathChosen = true;
			}
		}
		if (attempts > 4)
		{
			m_TargetPos = getPosition();
			break;
		}
		attempts++;
	} while (!pathChosen);
}

void Animal::wander()
{
	Vector2 animalPos = getPosition();
	Vector2 playerPos; //getGame().getPlayer().getPos();

	if (animalPos == playerPos)
		interact(Player(nullptr, Vector2(), 0)); //placeholder, getGame().getPlayer();

	if (m_PathCompleted)
	{
		chooseNewPosition();
		m_CurrentPath = m_PathFinder->findPath(getPosition(), m_TargetPos);
		m_PathCompleted = false;
		m_PathIndex = 0;
	}

	if (getPosition().v0() != m_CurrentPath.at(m_CurrentPath.size() - 1).v0() || getPosition().v1() != m_CurrentPath.at(m_CurrentPath.size() - 1).v1())
	{
		m_PathIndex++;
		setPriorLoc(getPosition());
		setPosition(m_CurrentPath.at(m_PathIndex));
		setBusy(true);
	}
	else
	{
		m_CurrentPath.clear();
		m_PathCompleted = true;
	}
}

void Animal::interact(const Player& player)
{
	if (m_Game == nullptr) // placeholder, game->getCurrentEncounter() == null
	{
		// game.setEncounter();
		// game.setInCombat();
	}
}

bool Animal::combatLogic(const MobileObject& target)
{
	return true; //placeholder, this will be implemented by herbivore and carnivore
}

bool Animal::Flee()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);
	int fleeing = dis(gen) % 4;
	if (fleeing == 1)
	{
		setFled(true);
		return true;
	}
	return false;
}

bool Animal::Attack(MobileObject& target)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);
	int successful = dis(gen) % 2;
	
	if (successful)
	{
		target.SufferHarm(m_Damage);
		return true;
	}
	return false;
}

