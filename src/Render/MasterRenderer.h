#pragma once
#include "EntityRenderer.h"
#include "TerrainRenderer.h"

class MasterRenderer
{
private:
	EntityRenderer* m_EntityRenderer = nullptr;
	TerrainRenderer *m_TerrainRenderer = nullptr;
	EntityShader *m_EntityShader = nullptr;
	TerrainShader *m_TerrainShader = nullptr;

	std::unordered_map<Model, std::vector<Entity>> m_Entities;
	Model m_TerrainModel;
	std::vector<Texture> m_BatchedTextures;

public:
	MasterRenderer(const std::string& eShaderSrc, const std::string& tShaderSrc);
	~MasterRenderer();

	void Clear() const;
	void Render(Camera& camera);
	void ProcessEntity(const Entity& entity);
	inline void AddTerrainModel(const Model& terrainModel) { m_TerrainModel = terrainModel; }
	inline void AddTerrainTextures(const std::vector<Texture>& batchedTextures) { m_BatchedTextures = batchedTextures; }
};