#include "AStarPathFinder.h"
#include "StationaryObject.h"
#include "Map.h"

#include <cmath>
#include <stdexcept>

AStarPathFinder::Tile::Tile()
{
	t_Position = Vector2();
	t_GCost = 0;
	t_HCost = 0.0;
	t_FCost = 0.0;
}

AStarPathFinder::Tile::Tile(AStarPathFinder* refrnc, Vector2 pos, bool obs)
{
	aRef = refrnc;
	t_Position = pos;
	t_GCost = 0;
	t_HCost = 0.0;
	t_FCost = 0.0;
	t_IsWall = obs;
}

void AStarPathFinder::Tile::addNeighbors()
{
	int j = (int)t_Position.v0();
	int i = (int)t_Position.v1();

	try
	{
		if (j < aRef->m_Grid.size() - 1)
			t_Neighbors.push_back(aRef->m_Grid.at(j + 1).at(i));
		if (j > 0)
			t_Neighbors.push_back(aRef->m_Grid.at(j - 1).at(i));
		if (i < aRef->m_Grid[0].size() - 1)
			t_Neighbors.push_back(aRef->m_Grid.at(j).at(i + 1));
		if (i > 0)
			t_Neighbors.push_back(aRef->m_Grid.at(j).at(i - 1));
	}
	catch (std::out_of_range& e)
	{
		fprintf(stderr, "pathfinder addNeighbors exception. pos(%d, %d). err: %s\n", j, i, e.what());
	}

}

AStarPathFinder::AStarPathFinder(Map* map, const std::vector<bool>& canWalk)
{
	m_Map = map;
	m_CanWalk = canWalk;
	setUpGrid(canWalk);
}

void AStarPathFinder::setUpGrid(const std::vector<bool>& canWalk)
{
	size_t cols = m_Map->getTerrainTiles().size();
	size_t rows = m_Map->getTerrainTiles().at(0).size();

	m_Grid = std::vector<std::vector<Tile>>(cols, std::vector<Tile>(rows, Tile()));
	for (uint32_t y = 0; y < cols; y++)
	{
		for (uint32_t x = 0; x < rows; x++)
		{
			Vector2 pos = Vector2((float)y, (float)x);
			bool isObs = isObstacle(pos, canWalk);
			m_Grid.at(y).at(x) = Tile(this, pos, isObs);
		}
	}

	/*for (std::vector<Tile>& col : m_Grid)
	{
		for (Tile& T : col)
			T.addNeighbors();
	}*/

	for (uint32_t y = 0; y < cols; y++)
	{
		for (uint32_t x = 0; x < rows; x++)
		{
			m_Grid.at(y).at(x).addNeighbors();
		}
	}
}

bool AStarPathFinder::isObstacle(const Vector2& pos, const std::vector<bool>& canWalk)
{
	bool canWalkGrass = canWalk.at(0);
	bool canWalkDesert = canWalk.at(1);
	bool canWalkWater = canWalk.at(2);
	bool hasObj = m_Map->getTerrainTiles().at((uint32_t)pos.v0()).at((uint32_t)pos.v1()).hasStatObj();
	StationaryObject* statObj = m_Map->getTerrainTiles().at((uint32_t)pos.v0()).at((uint32_t)pos.v1()).getStatObj();
	TerrainTile::TerrainType terrain = m_Map->getTerrainTiles().at((uint32_t)pos.v0()).at((uint32_t)pos.v1()).getTerrainType();

	switch (terrain)
	{
	case TerrainTile::GRASSLAND:
		if (canWalkGrass)
		{
			if (hasObj)
			{
				if (statObj->isPassable())
					return false;
			}
			else
				return false;
		}
		break;
	case TerrainTile::DESERT:
		if (canWalkDesert)
		{
			if (hasObj)
			{
				if (statObj->isPassable())
					return false;
			}
			else
				return false;
		}
		break;
	case TerrainTile::WATER:
		if (canWalkWater)
		{
			if (hasObj)
			{
				if (statObj->isPassable())
					return false;
			}
			else
				return false;
		}
		break;
	default:
		return true;
	}

	return true;
}

int AStarPathFinder::heuristic(const Tile& a, const Tile& b)
{
	int y1 = (int)a.getPosition().v0();
	int x1 = (int)a.getPosition().v1();
	int y2 = (int)b.getPosition().v0();
	int x2 = (int)b.getPosition().v1();

	return std::max(std::abs(y2 - y1), std::abs(x2 - x1));
}

std::vector<Vector2> AStarPathFinder::findPath(Vector2 start, Vector2 target)
{
	std::vector<Vector2> path;
	std::vector<Tile> openSet;
	std::vector<Tile> closedSet;

	for (auto& y : m_Grid)
	{
		for (Tile& x : y)
		{
			x.setGCost(0);
			x.setHCost(0.0);
			x.setFCost(0.0);
			x.setPrevious(nullptr);
		}
	}

	openSet.push_back(m_Grid.at((int)start.v0()).at((int)start.v1()));
	Tile targetTile = m_Grid.at((int)target.v0()).at((int)target.v1());

	while (openSet.size() > 0)
	{
		uint32_t lowestIndex = 0;
		for (uint32_t i = 0; i < openSet.size(); i++)
		{
			if (openSet.at(i).getFCost() < openSet.at(lowestIndex).getFCost())
				lowestIndex = i;
		}
		Tile current = openSet.at(lowestIndex);

		if (current == targetTile)
		{
			Tile temp = current;
			path.push_back(current.getPosition());
			while (temp.getPrevious() != nullptr)
			{
				path.push_back(temp.getPrevious()->getPosition());
				temp = *temp.getPrevious();
			}

			std::reverse(path.begin(), path.end());
			break;
		}

		auto it = std::find(openSet.begin(), openSet.end(), current);
		openSet.erase(it);
		closedSet.push_back(current);

		for (Tile& neighbor : current.getNeighbors())
		{
			//if neighbor is not in closedSet and it is not a wall (ie is passable)
			auto itr = std::find(closedSet.begin(), closedSet.end(), neighbor);
			if (itr == closedSet.end() && !neighbor.isWall())
			{
				int tempG = current.getGCost() + 1;
				auto found = std::find(openSet.begin(), openSet.end(), neighbor);
				if (found != openSet.end())
				{
					if (tempG < neighbor.getGCost())
						neighbor.setGCost(tempG);
				}
				else
				{
					neighbor.setGCost(tempG);
					openSet.push_back(neighbor);
				}

				neighbor.setHCost(heuristic(neighbor, targetTile));
				neighbor.setFCost(neighbor.getHCost() + neighbor.getGCost());
				neighbor.setPrevious(&current);
			}
		}
	}
	if (openSet.size() <= 0)
	{
		setUpGrid(m_CanWalk);
		path.push_back(start);
	}

	return path;
}

