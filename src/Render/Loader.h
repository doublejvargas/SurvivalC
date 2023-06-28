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
		const std::vector<unsigned int>& indices, const std::vector<float>& texIndices, const std::string& filename);

	GLuint LoadTexture(const std::string& filename);
	void UnbindVAO() const;

private:
	std::vector<GLuint> m_VAOS;
	std::vector<GLuint> m_VBOS;
	std::vector<GLuint> m_IBOS;
	std::vector<GLuint> m_Textures;

	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint layoutloc, unsigned int dimension, unsigned int bytesize, GLenum type, const void* data);
	void BindIndicesBuffer(const unsigned int* indices, unsigned int count);
};