#pragma once

#include <vector>
#include <string>
#include "Model.h"
#include "glm\glm.hpp"

// This class will help set up the models from the POV of OpenGL for rendering, in contrast to my other model classes that contain the game information and logic.
// Game classes containing game-info and logic will contain in addition these visual model information so that OpenGL can render them.
class Loader
{
public:
	Loader();
	~Loader();

	Model LoadToVAO(const std::vector<float>& positions, const std::vector<float>& texCoords, 
		const std::vector<uint32_t>& indices, const std::string& filename = "");
	
	// Overloaded for batch rendering
	Model LoadToVAO(const std::vector<float>& positions, const std::vector<float>& texCoords, const std::vector<uint32_t>& indices, 
		const std::vector<float>& texIndices, const std::string& filename = "");

	GLuint LoadTexture(const std::string& filename);
	void UnbindVAO() const;

private:
	std::vector<GLuint> m_VAOS;
	std::vector<GLuint> m_VBOS;
	std::vector<GLuint> m_IBOS;
	std::vector<GLuint> m_Textures;

	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint layoutloc, uint32_t dimension, uint32_t bytesize, GLenum type, const void* data);
	void BindIndicesBuffer(const uint32_t* indices, uint32_t count);
};