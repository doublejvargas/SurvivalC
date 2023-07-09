#pragma once
#include "Loader.h"
#include "TerrainTile.h"
#include <vector>

//Forward declaration to avoid circular #includes
class Game;

class Map
{
public:
	//Pixel size of a terrain tile
	static const int TILE_SIZE = 30;
	//Dimension of terrain grid, to be interpreted as m_N x m_N (square)
	static const uint32_t N_TILES = 50;
private:

	//2D vector of terrain tile objects. Corresponds to what is drawn by OpenGL.
	std::vector<std::vector<TerrainTile>> m_TerrainTiles;
	//OpenGL model for the terrain tiles.
	Model* m_TerrainMapModel = nullptr;

public:
	Map(Loader* loader);
	~Map();

	inline std::vector<std::vector<TerrainTile>> getTerrainTiles() const	{ return m_TerrainTiles; }
	inline Model& getTerrainMapModel() const								{ return *m_TerrainMapModel; }
	inline uint32_t GridDimensionX() const									{ return N_TILES; }
	inline uint32_t GridDimensionY() const									{ return N_TILES; }
	inline int getTileSize() const											{ return TILE_SIZE; }

private:
	// Sets up terrain objects on game logic side
	void SetUpTerrainMap();
	// Sets up terrain model on OpenGL side.
	Model GenerateOglTerrain(Loader* loader);
};