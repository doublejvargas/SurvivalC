#include "TerrainTileProcessor.h"
#include "Entity.h"
#include "Vector2.h"

std::vector<Entity> TerrainTileProcessor::ProcessTerrainTiles(const std::vector<std::vector<TerrainTile>>& tiles, Loader *loader)
{
	Model rock_model = loader->LoadToVAO(GENERIC_SQUARE_POS, GENERIC_SQUARE_UV, GENERIC_SQUARE_INDICES, "res/textures/rock.png");
	Model bush_model = loader->LoadToVAO(GENERIC_SQUARE_POS, GENERIC_SQUARE_UV, GENERIC_SQUARE_INDICES, "res/textures/bush.png");
	Model tree_model = loader->LoadToVAO(GENERIC_SQUARE_POS, GENERIC_SQUARE_UV, GENERIC_SQUARE_INDICES, "res/textures/tree.png");
	Model base_model = loader->LoadToVAO(GENERIC_SQUARE_POS, GENERIC_SQUARE_UV, GENERIC_SQUARE_INDICES, "res/textures/campFire.png");

	std::vector<Entity> entities;

	for (const std::vector<TerrainTile>& batch : tiles)
	{
		for (const TerrainTile& t : batch)
		{
			if (t.hasStatObj())
			{
				switch (t.getStatObjType())
				{
				case TerrainTile::ROCK:
					// positions scaled by tile size for accurate rendering, also reversed from map's (y, x) coordinate system to (x, y) for opengl
					entities.push_back(Entity(rock_model, Vector2::to_glm_vec2(t.getPosition().reverse()) * (float)Map::TILE_SIZE));
					break;
				case TerrainTile::BUSH:
					entities.push_back(Entity(bush_model, Vector2::to_glm_vec2(t.getPosition().reverse()) * (float)Map::TILE_SIZE));
					break;
				case TerrainTile::TREE:
					entities.push_back(Entity(tree_model, Vector2::to_glm_vec2(t.getPosition().reverse()) * (float)Map::TILE_SIZE));
					break;
				case TerrainTile::BASE:
					entities.push_back(Entity(base_model, Vector2::to_glm_vec2(t.getPosition().reverse()) * (float)Map::TILE_SIZE));
					break;
				case TerrainTile::NONE:
					break;
				default:
					break;

				}
			}
		}
	}

	return entities;
}

// TODO: positions have to be consistent with tile size in Map.h
const std::vector<float> TerrainTileProcessor::GENERIC_SQUARE_POS = {
	 0.0f,									0.0f,
	 (float)Map::TILE_SIZE,					0.0f,
	 (float)Map::TILE_SIZE,	(float)Map::TILE_SIZE,
	 0.0f,					(float)Map::TILE_SIZE
};

// clock wise ordering of vertices
const std::vector<float> TerrainTileProcessor::GENERIC_SQUARE_UV = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};


const std::vector<uint32_t> TerrainTileProcessor::GENERIC_SQUARE_INDICES = {
	0, 1, 2,
	2, 3, 0
};