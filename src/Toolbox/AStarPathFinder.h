#pragma once

#include <vector>
#include "Vector2.h"
#include "Game.h"

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
		Tile(AStarPathFinder* ref, Vector2 pos, bool obs);
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

		bool operator==(const Tile& T)
		{
			return (T.getPosition() == t_Position);
		}

		void operator=(const Tile& T)
		{
			aRef = T.getARef();
			t_Position = T.getPosition();
			t_GCost = T.getGCost();
			t_HCost = T.getHCost();
			t_FCost = T.getFCost();
			t_Neighbors = T.getNeighbors();
			t_Previous = T.getPrevious();
			t_IsWall = T.isWall();
		}
	};

private:
	std::vector<std::vector<Tile>> m_Grid;
	std::vector<bool> m_CanWalk;
	Game* m_Game = nullptr;

public:
	AStarPathFinder(Game* game, const std::vector<bool>& canWalk);

	void setUpGrid(Game* game, const std::vector<bool>& canWalk);
	bool isObstacle(Game* game, const Vector2& pos, const std::vector<bool>& canWalk);
	static int heuristic(const Tile& a, const Tile& b);
	
	// The actual A* pathfinder algorithm is implemented by findPathfunction.
	std::vector<Vector2> findPath(Vector2 start, Vector2 target);

	// Getter
	inline std::vector<std::vector<Tile>> getGrid() const { return m_Grid; }
};