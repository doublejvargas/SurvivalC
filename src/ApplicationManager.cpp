#include <stdio.h>
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "ApplicationManager.h"
#include "Game.h"
#include "Player.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "Map.h "
#include "PerlinNoise2D.h"
#include "glm/glm.hpp"
#include "Log.h"
#include "TerrainTileProcessor.h"

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
	Loader loader;
	Game game(&loader);
	MasterRenderer renderer("res/shaders/Shader2D", "res/shaders/TerrainShader2D");
	Camera camera;

	std::vector<Entity> entities = TerrainTileProcessor::ProcessTerrainTiles(game.getMap()->getTerrainTiles(), &loader);

	for (const Entity& e : entities)
		renderer.ProcessEntity(e);

	Model playerModel = loader.LoadToVAO(TerrainTileProcessor::GENERIC_SQUARE_POS, TerrainTileProcessor::GENERIC_SQUARE_UV, 
		TerrainTileProcessor::GENERIC_SQUARE_INDICES, "res/textures/player.png");
	glm::vec2 playerPos = (float)Map::TILE_SIZE * Vector2::to_glm_vec2(game.getPlayer()->getPosition().reverse());
	Entity playerInstance(playerModel, playerPos);
	
	renderer.ProcessEntity(playerInstance);

	camera.centerOn(glm::vec3(playerPos, -1));

	Model mapModel = game.getMap()->getTerrainMapModel();
	Entity mapInstance(mapModel, glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(1, 1));

	std::vector<Texture> textures;
	textures.push_back(Texture(loader.LoadTexture("res/textures/water.png")));
	textures.push_back(Texture(loader.LoadTexture("res/textures/grass.png")));
	textures.push_back(Texture(loader.LoadTexture("res/textures/desert.png")));

	renderer.AddTerrainModel(mapModel);
	renderer.AddTerrainTextures(textures);

	printf("Vertex count: %i\n", mapModel.vertexCount());

	printf("Running game loop...\n");
	double prevTime = glfwGetTime();
	int frameCount = 0;

	// TODO: Game loop! We might need to create an actual game loop function so that we don't write everything here.
	while (m_DisplayManager->IsWindowOpen())
	{
		/* Render here */
		renderer.Clear();
		camera.Move();
		
		renderer.Render(camera);

		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}

	printf("Game loop terminated\n");
}
