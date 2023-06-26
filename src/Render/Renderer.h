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

private:
	glm::mat4 m_OrthoMatrix;
};