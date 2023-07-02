#include "MasterRenderer.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"

MasterRenderer::MasterRenderer(const std::string& eShaderSrc, const std::string& tShaderSrc)
{
	//Creation of dynamic variables requires deletion in destructor!
	m_EntityShader = new EntityShader(eShaderSrc);
	m_TerrainShader = new TerrainShader(tShaderSrc);
	m_EntityRenderer = new EntityRenderer(*m_EntityShader);
	m_TerrainRenderer = new TerrainRenderer(*m_TerrainShader);

	// Set clear color
	GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));

	//TODO: give this constructor access to windows' width and height. for now, hard-code it.
	m_OrthoMatrix = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);

	m_EntityShader->Bind();
	m_EntityShader->LoadProjectionMatrix(m_OrthoMatrix);
	m_EntityShader->Unbind();

	m_TerrainShader->Bind();
	m_TerrainShader->LoadProjectionMatrix(m_OrthoMatrix);
	m_TerrainShader->Unbind();
}

MasterRenderer::~MasterRenderer()
{
	delete m_EntityShader;
	delete m_TerrainShader;
	delete m_EntityRenderer;
	delete m_TerrainRenderer;
}

void MasterRenderer::Clear() const
{
	// Clear
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void MasterRenderer::Render(Entity& entity, Model& terrainModel, const glm::vec2& terrainPos, std::vector<Texture>& textures, Camera& camera)
{
	//Render terrain
	m_TerrainShader->Bind();
	m_TerrainShader->LoadViewMatrix(camera);
	m_TerrainRenderer->Render(terrainModel, *m_TerrainShader, glm::vec2(0, 0), textures);
	m_TerrainShader->Unbind();

	//Render entities
	m_EntityShader->Bind();
	m_EntityShader->LoadViewMatrix(camera);
	m_EntityRenderer->Render(entity, *m_EntityShader);
	m_EntityShader->Unbind();
}

