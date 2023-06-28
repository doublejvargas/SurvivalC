#include "Renderer.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer(Shader& shader)
{
	// Set clear color
	GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));

	//TODO: give this constructor access to windows' width and height. for now, hard-code it.
	m_OrthoMatrix = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

	shader.Bind();
	shader.LoadProjectionMatrix(m_OrthoMatrix);
	shader.Unbind();
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	// Clear
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Render(Entity& entity, Shader& shader)
{
	// Get model (access to texture + VAO)
	Model model = entity.GetModel();

	// Bind the model's VAO
	GLCall(glBindVertexArray(model.VaoID()));
	// Enable the attrib arrays / layout locations
	GLCall(glEnableVertexAttribArray(0)); // positions
	GLCall(glEnableVertexAttribArray(1)); // texture coordinates
	// Load transformation matrix for this entity into the shader
	shader.LoadTransformMatrix(Shader::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Activate an OpenGL texture and tell it where the texture is
	Texture texture = model.GetTexture();
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.TextureID()));
	// Draw the model
	GLCall(glDrawElements(GL_TRIANGLES, model.VertexCount(), GL_UNSIGNED_INT, 0));
	// Disable attrib arrays / layout locations
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	// Unbind VAO
	GLCall(glBindVertexArray(0));
}

//Tentative
void Renderer::TerrainRender(Model& model, Shader& shader, const glm::vec2& pos, const std::string& texturefile)
{
	// Bind the model's VAO
	GLCall(glBindVertexArray(model.VaoID()));
	// Enable the attrib arrays / layout locations
	GLCall(glEnableVertexAttribArray(0)); // positions
	GLCall(glEnableVertexAttribArray(1)); // texture coordinates
	// Load transformation matrix for this entity into the shader
	shader.LoadTransformMatrix(Shader::CreateTransformationMatrix(pos, glm::vec2(0,0), glm::vec2(1, 1)));
	//// Load shine variables from texture
	//Texture texture = model.GetTexture();
	// Activate an OpenGL texture and tell it where the texture is
	Texture texture = model.GetTexture();
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.TextureID()));
	// Draw the model
	GLCall(glDrawElements(GL_TRIANGLES, model.VertexCount(), GL_UNSIGNED_INT, 0));
	// Disable attrib arrays / layout locations
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	// Unbind VAO
	GLCall(glBindVertexArray(0));
}

