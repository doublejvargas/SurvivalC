#include <iostream>
#include "DisplayManager.h"


DisplayManager::DisplayManager(int width /*= 1280*/, int height /*= 720*/, const std::string& title /*= "SURVIVAL"*/)
{
	m_Title = title;
	m_AspectRatio = (float)width / (float)height;

	// Create window using GLFW
	m_Window = glfwCreateWindow(width, height, m_Title.c_str(), NULL, NULL);

	if (m_Window != NULL)
	{
		std::cout << "Window created successfully" << std::endl;
		// Set OpenGL context to the window
		glfwMakeContextCurrent(m_Window);
		// Set OpenGL viewport to window's full size
		glViewport(0, 0, width, height);
		// Enable Vsync
		glfwSwapInterval(1);
	}

	else
		std::cerr << "ERROR: Failed to create window" << std::endl;
}

DisplayManager::~DisplayManager()
{
	// Cleanup GLFW
	glfwDestroyWindow(m_Window);
	std::cout << "Window destroyed successfully" << std::endl;
}

bool DisplayManager::IsWindowOpen() const
{
	return !glfwWindowShouldClose(m_Window);
}

void DisplayManager::UpdateDisplay() const
{
	// Tell GLFW to swap buffers
	glfwSwapBuffers(m_Window);
	// Tell GLFW to get window events
	glfwPollEvents();
}

// Computes frames
void DisplayManager::ShowFPS(double& prevTime, int& frameCount)
{
	double currentTime = glfwGetTime();
	frameCount++;
	if (currentTime - prevTime >= 1.0)
	{
		glfwSetWindowTitle(m_Window, (m_Title + " | FPS: " + std::to_string(frameCount)).c_str());
		frameCount = 0;
		prevTime = currentTime;
	}
}
