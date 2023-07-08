#pragma once
#include "Loader.h"
#include "TerrainTile.h"
#include <vector>

//Forward declaration to avoid circular #includes
class Game;

class Map
{
private:
	//Pixel size of a terrain tile
	static const int m_TILE_SIZE	= 30;
	//Dimension of terrain grid, to be interpreted as m_N x m_N (square)
	static const uint32_t m_N			= 50;
	//2D vector of terrain tile objects. Corresponds to what is drawn by OpenGL.
	std::vector<std::vector<TerrainTile>> m_TerrainTiles;
	//OpenGL model for the terrain tiles.
	Model* m_TerrainMapModel = nullptr;

public:
	Map(Loader* loader);
	~Map();

	inline std::vector<std::vector<TerrainTile>> getTerrainTiles() const	{ return m_TerrainTiles; }
	inline Model& getTerrainMapModel() const								{ return *m_TerrainMapModel; }
	inline uint32_t GridDimensionX() const									{ return m_N; }
	inline uint32_t GridDimensionY() const									{ return m_N; }
	inline int getTileSize() const											{ return m_TILE_SIZE; }

private:
	// Sets up terrain objects on game logic side
	void SetUpTerrainMap();
	// Sets up terrain model on OpenGL side.
	Model GenerateOglTerrain(Loader* loader);
};