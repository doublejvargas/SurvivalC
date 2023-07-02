#include "TerrainRenderer.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"

TerrainRenderer::TerrainRenderer(TerrainShader& shader)
{
	// Set clear color
	GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));

	//TODO: give this constructor access to windows' width and height. for now, hard-code it.
	m_OrthoMatrix = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

	shader.Bind();
	shader.LoadProjectionMatrix(m_OrthoMatrix);
	shader.Unbind();
}

void TerrainRenderer::Clear() const
{
	// Clear
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void TerrainRenderer::Render(Model& model, TerrainShader& shader, const glm::vec2& pos, std::vector<Texture>& textures)
{
	// Bind the model's VAO
	GLCall(glBindVertexArray(model.VaoID()));

	// Enable the attrib arrays / layout locations
	GLCall(glEnableVertexAttribArray(0)); // positions
	GLCall(glEnableVertexAttribArray(1)); // texture coordinates
	GLCall(glEnableVertexAttribArray(2)); // texture index

	// Load transformation matrix for this entity into the shader
	shader.LoadTransformMatrix(TerrainShader::CreateTransformationMatrix(pos, glm::vec2(0, 0), glm::vec2(1, 1))); //todo: does terrainshader require any differences here?

	// Activate an OpenGL texture and tell it where the texture is
	GLCall(glBindTextureUnit(0, textures[0].TextureID()));
	GLCall(glBindTextureUnit(1, textures[1].TextureID()));
	GLCall(glBindTextureUnit(2, textures[2].TextureID()));

	// Draw the model
	GLCall(glDrawElements(GL_TRIANGLES, model.VertexCount(), GL_UNSIGNED_INT, 0));

	// Disable attrib arrays / layout locations
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));

	// Unbind VAO
	GLCall(glBindVertexArray(0));
}


