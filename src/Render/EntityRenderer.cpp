#include "EntityRenderer.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"
#include "DisplayManager.h"

EntityRenderer::EntityRenderer(EntityShader& shader)
{
	// Set clear color
	GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));

	m_OrthoMatrix = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
	shader.Bind();
	shader.LoadProjectionMatrix(m_OrthoMatrix);
	shader.Unbind();
}

void EntityRenderer::Clear() const
{
	// Clear
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void EntityRenderer::Render(Entity& entity, EntityShader& shader)
{
	// Get model (access to texture + VAO)
	Model model = entity.GetModel();

	// Bind the model's VAO
	GLCall(glBindVertexArray(model.VaoID()));

	// Enable the attrib arrays / layout locations
	GLCall(glEnableVertexAttribArray(0)); // positions
	GLCall(glEnableVertexAttribArray(1)); // texture coordinates
	//GLCall(glEnableVertexAttribArray(2)); // texture index // TODO:May need to reenable this for batch rendering of entities

	// Load transformation matrix for this entity into the shader
	shader.LoadTransformMatrix(EntityShader::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));

	// Activate an OpenGL texture and tell it where the texture is
	Texture texture = model.GetTexture();
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.TextureID()));

	// Draw the model
	GLCall(glDrawElements(GL_TRIANGLES, model.VertexCount(), GL_UNSIGNED_INT, 0));

	// Disable attrib arrays / layout locations
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	//GLCall(glDisableVertexAttribArray(2));

	// Unbind VAO
	GLCall(glBindVertexArray(0));
}