#pragma once

#include "Entity.h"
#include "EntityShader.h"

class EntityRenderer
{
public:

	EntityRenderer(EntityShader& shader);

	void Clear() const;
	
	void Render(Entity& entity, EntityShader& shader);

private:
	glm::mat4 m_OrthoMatrix;
};