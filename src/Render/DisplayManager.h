#pragma once
#include <string>
#include <GLFW/glfw3.h>

class DisplayManager
{

public:
	DisplayManager(int width = 1280, int height = 720, const std::string& title = "SURVIVAL");
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
