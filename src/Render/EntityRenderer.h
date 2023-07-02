#pragma once

#include "Entity.h"
#include "EntityShader.h"
#include <unordered_map>

class EntityRenderer
{
private:
	glm::mat4 m_OrthoMatrix;

public:

	EntityRenderer(EntityShader& shader);

	void Clear() const;
	void Render(const std::unordered_map<Model, std::vector<Entity>>& entities, EntityShader& shader);

private:
	void setOglState(const Model& model, EntityShader& shader);
	void resetOglState();
	void prepareInstance(const Entity& entity, EntityShader& shader);

};