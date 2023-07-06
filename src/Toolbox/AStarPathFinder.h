#pragma once

#include "Vector2.h"
#include <vector>

//class Game;
class Map;
class AStarPathFinder
{
private:
	// Private class that represents a map tile.
	class Tile
	{
	private:
		AStarPathFinder* aRef = nullptr;
		Vector2 t_Position;
		int t_GCost;
		double t_HCost;
		double t_FCost;
		std::vector<Tile> t_Neighbors;
		Tile* t_Previous = nullptr;
		bool t_IsWall = false;
	public:
		Tile();
		Tile(AStarPathFinder* refrnc, Vector2 pos, bool obs);
		void addNeighbors();

		inline int getGCost() const { return t_GCost; }
		inline double getHCost() const { return t_HCost; }
		inline double getFCost() const { return t_FCost; }
		inline Vector2 getPosition() const { return t_Position; }
		inline std::vector<Tile> getNeighbors() const { return t_Neighbors; }
		inline Tile* getPrevious() const { return t_Previous; }
		inline AStarPathFinder* getARef() const { return aRef; }
		inline bool isWall() const { return t_IsWall; }

		inline void setPrevious(Tile* t) { t_Previous = t; }
		inline void setGCost(int gcost) { t_GCost = gcost; }
		inline void setHCost(double hcost) { t_HCost = hcost; }
		inline void setFCost(double fcost) { t_FCost = fcost; }

		friend bool operator==(const Tile& t1, const Tile& t2)
		{
			return (t1.getPosition() == t2.getPosition());
		}


		Tile& operator=(const Tile& t)
		{
			aRef = t.getARef();
			t_Position = t.getPosition();
			t_GCost = t.getGCost();
			t_HCost = t.getHCost();
			t_FCost = t.getFCost();
			t_Neighbors = t.getNeighbors();
			t_Previous = t.getPrevious();
			t_IsWall = t.isWall();

			return *this;
		}
	};

private:
	std::vector<std::vector<Tile>> m_Grid;
	std::vector<bool> m_CanWalk;
	Map* m_Map = nullptr;

public:
	AStarPathFinder(Map* map, const std::vector<bool>& canWalk);

	void setUpGrid(const std::vector<bool>& canWalk);
	bool isObstacle(const Vector2& pos, const std::vector<bool>& canWalk);
	static int heuristic(const Tile& a, const Tile& b);
	
	// The actual A* pathfinder algorithm is implemented by findPathfunction.
	std::vector<Vector2> findPath(Vector2 start, Vector2 target);

	// Getter
	inline std::vector<std::vector<Tile>> getGrid() const { return m_Grid; }
};