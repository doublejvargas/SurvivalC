#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position);
	Camera();
	void Move();

	inline glm::vec3 GetPosition() { return m_Position; }
private:
	glm::vec3 m_Position;

};
