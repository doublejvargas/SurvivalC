#include <stdio.h>
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "ApplicationManager.h"
#include "Log.h"

ApplicationManager::ApplicationManager()
{

	// Initialize GLFW
	if (glfwInit())
	{
		printf("GLFW initialized successfully \n");

		//Create Display Manager (don't forget to delete the pointer in destructor)
		// This dynamic creation of a DisplayManager object creates a context, sets the context current, and creates a window with a title. See DisplayManager constructor.
		m_DisplayManager = new DisplayManager(640, 480, "SURVIVAL");

		//Initialize GLEW after GLFW and window
		GLenum status = glewInit();
		if (status != GLEW_OK)
			printf("ERROR: GLEW failed to initialize \n%s", glewGetErrorString(status));
		else
		{
			printf("GLEW initialized successfully\n");
			//m_DisplayManager->initializeImGui(); // initialize ImGUI after GLFW and GLEW.
		}

		printf("OpenGL version: %s\n", glGetString(GL_VERSION));	// print opengl version
	}
	else
	{
		printf("GLFW failed to initialize\n");
	}
}

ApplicationManager::~ApplicationManager()
{
	// Delete the display object (calls DisplayManager destructor) and clean up GLFW
	delete m_DisplayManager;
	glfwTerminate();
	printf("GLFW terminated successfully\n");
}

void ApplicationManager::Start()
{
	printf("C++ Standard: %i\n", __cplusplus);


	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer); // vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //index buffer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //vertex buffer specification

	printf("Running game loop...\n");

	double prevTime = glfwGetTime();
	int frameCount = 0;

	// Game loop! We might need to create an actual game loop function so that we don't write everything here.
	while (m_DisplayManager->IsWindowOpen())
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}
	// we may need to do some opengl cleanup here. eg. shaders, renderers, unbindings, etc..
	
	printf("Game loop terminated\n");
}
