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

	glm::mat4 m_OrthoMatrix;

public:
	MasterRenderer(const std::string& eShaderSrc, const std::string& tShaderSrc);
	~MasterRenderer();

	void Clear() const;
	void Render(Entity& entity, Model& terrainModel, const glm::vec2& terrainPos, std::vector<Texture>& textures, Camera& camera);
};