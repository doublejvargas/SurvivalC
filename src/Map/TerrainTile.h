#pragma once
#include "GameObject.h"

class StationaryObject;
// NOTE: this object's position is stored as (y, x), but should be used/read traditionally in this program as (x,y), especially for OpenGl.
class TerrainTile : public GameObject
{

public:
	enum StatObjType { ROCK, BUSH, TREE, BASE, NONE };
	enum TerrainType { WATER, GRASSLAND, DESERT };

	TerrainTile(float perlinVal, const Vector2& pos);

	inline StationaryObject* getStatObj()	const { return m_StatObj; }
	inline StatObjType getStatObjType()	const { return m_StatObjType; }
	inline TerrainType getTerrainType()	const { return m_TerrainType; }
	inline bool hasStatObj()			const { return m_hasStatObj; }
	inline bool isRevealedOnMiniMap()	const { return m_isRevealedOnMiniMap; }

	inline void setHasStatObj(bool val) 
	{ 
		m_hasStatObj = val;
		if (!val)
		{
			m_StatObj = nullptr;
			m_StatObjType = StatObjType::NONE;
		}
			
	}
	inline void setStatObjType(StatObjType type)	{ m_StatObjType = type; }
	inline void setStatObj(StationaryObject* obj)	{ m_StatObj = obj; }
	//inline void nullStatObj()						{ m_StatObj = nullptr; m_hasStatObj = false; }
	inline void setIsRevealedOnMiniMap(bool flag)	{ m_isRevealedOnMiniMap = flag; }


private:
	TerrainType m_TerrainType;
	StatObjType m_StatObjType;
	StationaryObject* m_StatObj = nullptr;
	bool m_hasStatObj;
	bool m_isRevealedOnMiniMap;

	void grasslandSetup();
	void desertSetup();
};