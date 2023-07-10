#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position);
	Camera();
	void Move();
	void centerOn(const glm::vec3 pos);

	inline glm::vec3 getPosition() const{ return m_Position; }
	inline void setPosition(const glm::vec3 pos) { m_Position = pos; }

private:
	glm::vec3 m_Position;

};
