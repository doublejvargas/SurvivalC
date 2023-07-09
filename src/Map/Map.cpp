#include "Map.h"
#include "PerlinNoise2D.h"
#include <unordered_map>

Map::Map(Loader* loader)
{
	SetUpTerrainMap();
	m_TerrainMapModel = new Model(GenerateOglTerrain(loader));
}

Map::~Map()
{
	delete m_TerrainMapModel;
}

void Map::SetUpTerrainMap()
{
	//m_TerrainTiles.reserve(m_N);
	m_TerrainTiles = std::vector<std::vector<TerrainTile>>(N_TILES, std::vector<TerrainTile>(N_TILES, TerrainTile(0.0f, Vector2())));

	PerlinNoise2D noise;
	noise.init();
	float scale = 2.5f; //todo changeback to 2.0f
	for (int y = 0; y < N_TILES; y++)
	{
		for (int x = 0; x < N_TILES; x++)
		{
			float x1 = x * scale / N_TILES;
			float y1 = y * scale / N_TILES;
			//KEY: this position is stored as (y,x) for vector/array purposes. For actual
			// use of this data, it should be used/read traditionally as (x,y), especially for openGl.
			m_TerrainTiles.at(y).at(x) = TerrainTile(noise.value(x1, y1), Vector2((float)y, (float)x));
		}
	}
}

Model Map::GenerateOglTerrain(Loader* loader)
{
	
	uint32_t GRID_SIZE = N_TILES * N_TILES;
	uint32_t numVertices = GRID_SIZE * 4;
	std::vector<float> positions(numVertices * 2, 0.0f);
	std::vector<float> texCoords(numVertices * 2, 0.0f);
	std::vector<uint32_t> indices(6 * GRID_SIZE,  0);
	std::vector<float> texIndices(numVertices, 0.0f);

	// Model positions
	uint32_t idx = 0;
	for (uint32_t y = 0; y < N_TILES; y++)
	{
		for (uint32_t x = 0; x < N_TILES; x++)
		{
			//Top left vertex x
			positions[idx + 0] = (float)x * TILE_SIZE;
			// Top left vertex y
			positions[idx + 1] = (float)y * TILE_SIZE;
			// Top right vertex x
			positions[idx + 2] = (float)(x + 1) * TILE_SIZE;
			// Top right vertex y
			positions[idx + 3] = (float)y * TILE_SIZE;
			// Bottom right vertex x
			positions[idx + 4] = (float)(x + 1) * TILE_SIZE;
			// Bottom right vertex y
			positions[idx + 5] = (float)(y + 1) * TILE_SIZE;
			// Bottom left vertex x
			positions[idx + 6] = (float)x * TILE_SIZE;
			// Bottom left vertex y
			positions[idx + 7] = (float)(y + 1) * TILE_SIZE;
			idx += 8;
		}
	}

	// Model texture coordinates 
	for (uint32_t i = 0; i < texCoords.size(); i+=8)
	{
		texCoords[i]	 = 0.0f;		texCoords[i + 1] = 0.0f;
		texCoords[i + 2] = 1.0f;		texCoords[i + 3] = 0.0f;
		texCoords[i + 4] = 1.0f;		texCoords[i + 5] = 1.0f;
		texCoords[i + 6] = 0.0f;		texCoords[i + 7] = 1.0f;
	}

	// Model indices
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

	// Model texture indices
	idx = 0;
	for (int y = 0; y < N_TILES; y++)
	{
		for (int x = 0; x < N_TILES; x++)
		{
			TerrainTile t = m_TerrainTiles.at(y).at(x);
			if (t.getTerrainType() == TerrainTile::WATER)
			{
				texIndices[idx + 0] = 0.0f;
				texIndices[idx + 1] = 0.0f;
				texIndices[idx + 2] = 0.0f;
				texIndices[idx + 3] = 0.0f;
			}
			else if (t.getTerrainType() == TerrainTile::GRASSLAND)
			{
				texIndices[idx + 0] = 1.0f;
				texIndices[idx + 1] = 1.0f;
				texIndices[idx + 2] = 1.0f;
				texIndices[idx + 3] = 1.0f;
			}
			else // TerrainTile::DESERT
			{
				texIndices[idx + 0] = 2.0f;
				texIndices[idx + 1] = 2.0f;
				texIndices[idx + 2] = 2.0f;
				texIndices[idx + 3] = 2.0f;
			}

			idx += 4;
		}
	}

	return loader->LoadToVAO(positions, texCoords, indices, texIndices);
}
