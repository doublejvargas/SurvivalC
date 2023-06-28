#include "Map.h"
#include "Noise.h"
#include <unordered_map>

Map::Map(Game* game, Loader* loader)
{
	Noise noise(m_NUM_TILES_Y, m_NUM_TILES_X);
	std::vector<std::vector<float>> perlinVals = noise.NoiseArray();

	SetUpTerrainMap(perlinVals, game);

	Model m = GenerateOglTerrain(loader);
	m_TerrainMapModel = &m;
}

void Map::SetUpTerrainMap(std::vector<std::vector<float>> perVal, Game* game)
{
	m_TerrainTiles = std::vector<std::vector<TerrainTile>>(m_NUM_TILES_Y, std::vector<TerrainTile>(m_NUM_TILES_X, TerrainTile(0.0f, game, Vector2(0, 0))));
	for (int y = 0; y < m_NUM_TILES_Y; y++)
	{
		for (int x = 0; x < m_NUM_TILES_X; x++)
		{
			//KEY: this position is stored as (y,x) for vector/array purposes. For actual
			// use of this data, it should be used/read traditionally as (x,y), especially for openGl.
			m_TerrainTiles[y][x] = TerrainTile(perVal[y][x], game, Vector2(y, x));
		}
	}
}

Model Map::GenerateOglTerrain(Loader* loader)
{
	
	uint32_t GRID_SIZE = m_N * m_N;
	uint32_t numVertices = GRID_SIZE * 4;
	std::vector<float> positions(numVertices * 2, 0.0f);
	std::vector<float> texCoords(numVertices * 2, 0.0f);
	std::vector<unsigned int> indices(6 * GRID_SIZE,  0);

	//std::unordered_map<std::pair<int, int>, float> cache;

	uint32_t idx = 0;
	for (uint32_t y = 0; y < m_N; y++)
	{
		for (uint32_t x = 0; x < m_N; x++)
		{
			//Top left vertex x
			positions[idx + 0] = (float)x * m_TILE_SIZE;
			// Top left vertex y
			positions[idx + 1] = (float)y * m_TILE_SIZE;
			// Top right vertex x
			positions[idx + 2] = (float)(x + 1) * m_TILE_SIZE;
			// Top right vertex y
			positions[idx + 3] = (float)y * m_TILE_SIZE;
			// Bottom right vertex x
			positions[idx + 4] = (float)(x + 1) * m_TILE_SIZE;
			// Bottom right vertex y
			positions[idx + 5] = (float)(y + 1) * m_TILE_SIZE;
			// Bottom left vertex x
			positions[idx + 6] = (float)x * m_TILE_SIZE;
			// Bottom left vertex y
			positions[idx + 7] = (float)(y + 1) * m_TILE_SIZE;
			idx += 8;
		}
	}

	for (uint32_t i = 0; i < texCoords.size(); i+=8)
	{
		texCoords[i]	 = 0.0f;		texCoords[i + 1] = 0.0f;
		texCoords[i + 2] = 1.0f;		texCoords[i + 3] = 0.0f;
		texCoords[i + 4] = 1.0f;		texCoords[i + 5] = 1.0f;
		texCoords[i + 6] = 0.0f;		texCoords[i + 7] = 1.0f;
	}


	uint32_t offset = 0;
	for (uint32_t i = 0; i < indices.size(); i+=6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	// TODO: By default I'm loading in a water texture because I just wanna test terrain generation... in future ill base texture on terrain tile type.
	return loader->LoadToVAO(positions, texCoords, indices, "res/textures/yuzu.png");
}
