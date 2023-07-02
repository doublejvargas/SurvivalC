#include <stdio.h>
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "ApplicationManager.h"
#include "Game.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "Map.h "
#include "PerlinNoise2D.h"
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
		m_DisplayManager = new DisplayManager(WINDOW_WIDTH, WINDOW_HEIGHT, "SURVIVAL");

		//Initialize GLEW after GLFW and window
		GLenum status = glewInit();
		if (status != GLEW_OK)
			printf("ERROR: GLEW failed to initialize \n%s", glewGetErrorString(status));
		else
		{
			printf("GLEW initialized successfully\n");
			//m_DisplayManager->initializeImGui(); // initialize ImGUI after GLFW and GLEW.
		}

		printf("OpenGL version: %s\n", glGetString(GL_VERSION));
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
	Game game;
	Loader loader;
	Map map(&game, &loader);
	MasterRenderer renderer("res/shaders/Shader2D", "res/shaders/TerrainShader2D");
	Camera camera;
	
	std::vector<float> positions = {
		 0.0f,   0.0f,
		 70.0f,  0.0f,
		 70.0f,  70.0,
		 0.0f,   70.0

// 		 600.0f, 0.0f,
// 		 900.0f, 0.0f,
// 		 900.0f, 300.0f,
// 		 600.0f, 300.0f
	};

	// clock wise ordering of vertices
	std::vector<float> texcoords= {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f

// 		0.0f, 0.0f,
// 		1.0f, 0.0f,
// 		1.0f, 1.0f,
// 		0.0f, 1.0f
	};


	std::vector<uint32_t> indices = {
		0, 1, 2, 2, 3, 0
/*		4, 5, 6, 6, 7, 4*/
	};

	std::vector<float> texindices = {
		0, 0, 0, 0,
		2, 2, 2, 2
	};

	Model squareModel = loader.LoadToVAO(positions, texcoords, indices, "res/textures/yuzu.png");
	Entity squareInstance(squareModel, glm::vec2(200, 200), glm::vec2(0, 0), glm::vec2(1, 1));

	Model mapModel = map.GetTerrainMapModel();
	Entity mapInstance(mapModel, glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(1, 1));

	std::vector<Texture> textures;
	textures.push_back(loader.LoadTexture("res/textures/water.png"));
	textures.push_back(loader.LoadTexture("res/textures/grass.png"));
	textures.push_back(loader.LoadTexture("res/textures/desert.png"));

	printf("Vertex count: %i\n", mapModel.VertexCount());

	printf("Running game loop...\n");
	double prevTime = glfwGetTime();
	int frameCount = 0;

	// TODO: Game loop! We might need to create an actual game loop function so that we don't write everything here.
	while (m_DisplayManager->IsWindowOpen())
	{
		/* Render here */
		renderer.Clear();
		camera.Move();
		
		renderer.Render(squareInstance, mapModel, glm::vec2(0, 0), textures, camera);

		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}

	printf("Game loop terminated\n");
}
