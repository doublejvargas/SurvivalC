#pragma once

#include "TerrainTile.h"
#include <vector>

// Todo, have Game get loader and get rid of that parameter.
class Map
{
private:
	static const uint32_t m_TILE_SIZE = 30;
	static const uint32_t m_N = 20;
	static const uint32_t m_NUM_TILES_Y = 100;
	static const uint32_t m_NUM_TILES_X = 100;

	std::vector<std::vector<TerrainTile>> m_TerrainTiles;

	Model* m_TerrainMapModel = nullptr;

public:
	//TODO: have game have a GetLoader method, and eliminate loader parameter.
	Map(Game* game, Loader* loader);

	inline std::vector<std::vector<TerrainTile>> GetTerrainTiles() const { return m_TerrainTiles; }
	inline Model* GetTerrainMapModel() const { return m_TerrainMapModel; }
	inline uint32_t GetNumTilesX() const { return m_NUM_TILES_X; }
	inline uint32_t GetNumTilesY() const { return m_NUM_TILES_Y; }

private:
	void SetUpTerrainMap(std::vector<std::vector<float>> perVal, Game* game);

	// Function creates the model for the terrain based on the terrain tiles. This is for OpenGL rendering.
	Model GenerateOglTerrain(Loader* loader);
};