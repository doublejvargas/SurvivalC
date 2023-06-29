#pragma once
#include "Model.h"
#include "Loader.h"
#include "TerrainTile.h"
#include <vector>

// Todo, have Game get loader and get rid of that parameter.
class Map
{
private:
	//Pixel size of a terrain tile
	static const uint32_t m_TILE_SIZE	= 30;
	//Dimension of terrain grid, to be interpreted as m_N x m_N (square)
	static const uint32_t m_N			= 30;
	//2D vector of terrain tile objects. Corresponds to what is drawn by OpenGL.
	std::vector<std::vector<TerrainTile>> m_TerrainTiles;
	//OpenGL model for the terrain tiles.
	Model* m_TerrainMapModel = nullptr;

public:
	//TODO: have game have a GetLoader method, and eliminate loader parameter.
	Map(Game* game, Loader* loader);
	~Map();

	inline std::vector<std::vector<TerrainTile>> GetTerrainTiles() const { return m_TerrainTiles; }
	inline Model& GetTerrainMapModel() const { return *m_TerrainMapModel; }
	inline uint32_t GridDimensionX() const { return m_N; }
	inline uint32_t GridDimensionY() const { return m_N; }

private:
	// Sets up terrain objects on game logic side
	void SetUpTerrainMap(Game* game);
	// Sets up terrain model on OpenGL side.
	Model GenerateOglTerrain(Loader* loader);
};