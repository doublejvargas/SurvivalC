#pragma once

#include "TerrainTile.h"
#include <vector>

// Todo, have Game get loader and get rid of that parameter.
class Map
{
private:
	static const uint32_t m_TILE_SIZE = 30;
	static const uint32_t m_N = 50;
	static const uint32_t m_NUM_TILES_Y = 50; //these must be the same as m_N!!
	static const uint32_t m_NUM_TILES_X = 50;

	std::vector<std::vector<TerrainTile>> m_TerrainTiles;

	Model* m_TerrainMapModel = nullptr;

public:
	//TODO: have game have a GetLoader method, and eliminate loader parameter.
	Map(Game* game, Loader* loader);
	~Map();

	inline std::vector<std::vector<TerrainTile>> GetTerrainTiles() const { return m_TerrainTiles; }
	inline Model& GetTerrainMapModel() const { return *m_TerrainMapModel; }
	inline uint32_t GetNumTilesX() const { return m_NUM_TILES_X; }
	inline uint32_t GetNumTilesY() const { return m_NUM_TILES_Y; }

private:
	void SetUpTerrainMap(Game* game);
	// Function creates the model for the terrain based on the terrain tiles. This is for OpenGL rendering.
	Model GenerateOglTerrain(Loader* loader);
};