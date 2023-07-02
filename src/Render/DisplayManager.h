#pragma once
#include <string>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class DisplayManager
{

public:
	DisplayManager(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, const std::string& title = "SURVIVAL");
	virtual ~DisplayManager();

	bool IsWindowOpen() const;
	void UpdateDisplay() const;

	inline float GetAspectRatio() const { return m_AspectRatio; }
	inline GLFWwindow* GetWindow() const { return m_Window; }

	void ShowFPS(double& prevTime, int& frameCount);

private:
	GLFWwindow* m_Window;
	float m_AspectRatio;
	std::string m_Title;
};
