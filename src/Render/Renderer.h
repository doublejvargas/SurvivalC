#pragma once

#include "Entity.h"
#include "Shader.h"

class Renderer
{
public:

	Renderer(Shader& shader);
	~Renderer();

	void Clear() const;
	
	void Render(Entity& entity, Shader& shader);
	//Tentative
	void TerrainRender(Model& model, Shader& shader, const glm::vec2& pos, const std::string& texturefile);
	

private:
	glm::mat4 m_OrthoMatrix;
};