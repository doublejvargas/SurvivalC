#include "Camera.h"
#include "DisplayManager.h"
#include <GLFW/glfw3.h>

Camera::Camera(const glm::vec3& position)
	: m_Position(position)
{
}

Camera::Camera()
{
	m_Position = glm::vec3(0, 0, -1);
}

void Camera::Move()
{
	float sens = 5.0f;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		m_Position.y += sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		m_Position.y -= sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		m_Position.x -= sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		m_Position.x += sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Q) == GLFW_PRESS)
		m_Position.z -= sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
		m_Position.z += sens;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS)
		m_Position = glm::vec3(0, 0, -1);
}

void Camera::centerOn(const glm::vec3 pos)
{
	m_Position = glm::vec3(pos.x - WINDOW_WIDTH / 2, pos.y - WINDOW_HEIGHT / 2, pos.z);
}

