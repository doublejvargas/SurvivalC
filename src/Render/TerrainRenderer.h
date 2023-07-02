#pragma once

#include "Entity.h"
#include "TerrainShader.h"

class TerrainRenderer
{
public:

	TerrainRenderer(TerrainShader& shader);

	void Clear() const;

	void Render(Model& model, TerrainShader& shader, const glm::vec2& pos, std::vector<Texture>& textures);

private:
	glm::mat4 m_OrthoMatrix;
};
