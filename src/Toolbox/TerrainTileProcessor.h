#pragma once

#include "Map.h"

class Entity;

class TerrainTileProcessor
{
public:

	static const std::vector<float> GENERIC_SQUARE_POS;
	static const std::vector<float> GENERIC_SQUARE_UV;
	static const std::vector<uint32_t> GENERIC_SQUARE_INDICES;
	//static const std::vector<float> texindices;

	static std::vector<Entity> ProcessTerrainTiles(const std::vector<std::vector<TerrainTile>>& tiles, Loader* loader);
};