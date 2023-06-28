#include <stdio.h>
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "ApplicationManager.h"
#include "Loader.h"
#include "Renderer.h" //includes Shader and Entity
#include "Map.h "
#include "glm/glm.hpp"
#include "Log.h"

ApplicationManager::ApplicationManager()
{

	// Initialize GLFW
	if (glfwInit())
	{
		printf("GLFW initialized successfully \n");

		//Create Display Manager (don't forget to delete the pointer in destructor)
		// This dynamic creation of a DisplayManager object creates a context, sets the context current, and creates a window with a title. See DisplayManager constructor.
		m_DisplayManager = new DisplayManager(1280, 720, "SURVIVAL");

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


	//float positions[6] = {
	//	-0.5f, -0.5f,
	//	 0.0f,  0.5f,
	//	 0.5f, -0.5f
	//};

	//unsigned int buffer;
	//glGenBuffers(1, &buffer); // vertex buffer
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0); //index buffer
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //vertex buffer specification

	Loader loader;
	Shader shader("res/shaders/Shader2D");
	Renderer renderer(shader);
	
	std::vector<float> positions = {
		 0.0f,   0.0f,
		 400.0f, 0.0f,
		 400.0f, 400.0f,
		 0.0f,   400.0f
	};

	// clock wise ordering of vertices
	std::vector<float> texcoords= {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};


	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	Model model = loader.LoadToVAO(positions,texcoords, indices, "res/textures/yuzu.png");
	Entity entity(model, glm::vec2(200, 200), glm::vec2(0, 0), glm::vec2(1, 1));

	Game game;

	Map map(&game, &loader);

	Model* mdl = map.GetTerrainMapModel();
	/*std::vector<std::vector<Entity>> entities(100, std::vector<Entity>(100, Entity(mdl, glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(1, 1))));
	for (int j = 0; j < 100; j++) {
		for (int i = 0; i < 100; i++) {
			entities[j][i] = Entity(mdl, glm::vec2(i * 10, j * 10), glm::vec2(0, 0), glm::vec2(1, 1));
		}
	}*/
	Entity mapinstance = Entity(*mdl, glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(1, 1));

	printf("Running game loop...\n");
	printf("Vertex count: %i", mdl->VertexCount()); // I noticed that for some reason the model2 variable changes value constantly throughout the program, including this part here.

	double prevTime = glfwGetTime();
	int frameCount = 0;

	// Game loop! We might need to create an actual game loop function so that we don't write everything here.
	while (m_DisplayManager->IsWindowOpen())
	{
		/* Render here */
		renderer.Clear();
		shader.Bind();

		/*for (int j = 0; j < 100; j++) {
			for (int i = 0; i < 100; i++) {
				renderer.Render(entities[j][i], shader);
			}
		}*/

		renderer.Render(mapinstance, shader);

		shader.Unbind();

		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}
	// We may need to do some opengl cleanup here. eg. shaders, renderers, unbindings, etc..
	
	printf("Game loop terminated\n");
}
