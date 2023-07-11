#pragma once

#include <glm\glm.hpp>
#include "Model.h"

// This class is OpenGL's equivalent of GameObject.
// While GameObject contains the an object's necessary information for the game logic,
// Entity contains an object's necessary information for rendering.
class Entity
{
public:
	Entity() : m_Position(glm::vec2(0, 0)), m_Rotation(glm::vec2(0, 0)) , m_Scale(glm::vec2(1, 1)) {}

	Entity(Model model, const glm::vec2& position, const glm::vec2& rotation = glm::vec2(0, 0), const glm::vec2& scale = glm::vec2(1, 1))
		: m_Model(model), m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

	Entity(const Entity& e)
		: m_Model(e.GetModel()), m_Position(e.GetPosition()), m_Rotation(e.GetRotation()), m_Scale(e.GetScale()) {}

	inline void ChangePosition(const glm::vec2& position) { m_Position += position; }
	inline void ChangeRotation(const glm::vec2& rotation) { m_Rotation += rotation; }
	inline void ChangeScale(const glm::vec2& scale)		  { m_Scale += scale; }

	inline Model GetModel()	const		 { return m_Model; }
	inline glm::vec2 GetPosition() const { return m_Position; }
	inline glm::vec2 GetRotation() const { return m_Rotation; }
	inline glm::vec2 GetScale() const	 { return m_Scale; }

	inline void SetPosition(const glm::vec2& position) { m_Position = position; }
	inline void SetRotation(const glm::vec2& rotation) { m_Rotation = rotation; }
	inline void SetScale(const glm::vec2& scale)	   { m_Scale = scale; }

private:
	Model m_Model;
	glm::vec2 m_Position; // Although GameObjects all have position, OpenGL will need this. 
	glm::vec2 m_Rotation;
	glm::vec2 m_Scale;
};
