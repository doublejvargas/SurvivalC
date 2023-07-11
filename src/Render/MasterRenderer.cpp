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

	m_Entities.reserve(1);
}

MasterRenderer::~MasterRenderer()
{
	delete m_EntityShader;
	delete m_TerrainShader;
	delete m_EntityRenderer;
	delete m_TerrainRenderer;

	m_Entities.clear();
	m_BatchedTextures.clear();
	printf("Deleted MasterRenderer's entities and textures\n");
}

void MasterRenderer::Clear() const
{
	// Clear
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void MasterRenderer::Render(Camera& camera)
{
	//Render terrain
	m_TerrainShader->Bind();
	m_TerrainShader->LoadViewMatrix(camera);
	m_TerrainRenderer->Render(m_TerrainModel, *m_TerrainShader, glm::vec2(0, 0), m_BatchedTextures);
	m_TerrainShader->Unbind();

	//Render entities
	m_EntityShader->Bind();
	m_EntityShader->LoadViewMatrix(camera);
	m_EntityRenderer->Render(m_Entities, *m_EntityShader);
	m_EntityShader->Unbind();
	
	// not sure if/why this step is necessary?
	//m_Entities.clear();
}

void MasterRenderer::ProcessEntity(Entity* entity)
{
	Model model = entity->GetModel();
	
	// if key "model" is NOT found in hash map, create a new batch and add a pair of (model, vector<entity>) to the Hash map.
	if (m_Entities.find(model) == m_Entities.end())
	{
		std::vector<Entity*> newBatch;
		newBatch.push_back(entity);
		m_Entities.insert(std::make_pair(model, newBatch));
	}
	// if that model already exists in Hash map, add the entity. 
	else
		m_Entities.at(model).push_back(entity);
}

