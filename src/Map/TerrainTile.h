#pragma once

#include "GameObject.h"
#include "StationaryObject.h"
#include "Entity.h"
#include "Loader.h"

class TerrainTile : protected GameObject
{
//private:
//	const float m_SIZE = 100;
//	const float m_VERTEX_COUNT = 128;

public:
	enum StatObjType { ROCK, BUSH, TREE, BASE, NONE };
	enum TerrainType { WATER, GRASSLAND, DESERT };

	TerrainTile(float perlinVal, Game* game, const Vector2& pos);

	inline StationaryObject* StatObj()	const { return m_StatObj; }
	inline StatObjType getStatObjType()	const { return m_StatObjType; }
	inline TerrainType getTerrainType()	const { return m_TerrainType; }
	inline bool hasStatObj()			const { return m_hasStatObj; }
	inline bool isRevealedonMiniMap()	const { return m_isRevealedOnMiniMap; }

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


private:
	TerrainType m_TerrainType;
	StatObjType m_StatObjType;
	StationaryObject* m_StatObj;
	bool m_hasStatObj;
	bool m_isRevealedOnMiniMap;

	void grasslandSetup();
	void desertSetup();

};