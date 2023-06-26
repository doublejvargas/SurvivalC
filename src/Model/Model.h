#pragma once

#include "Texture.h"

class Model
{
public:
	Model(GLuint vaoID, unsigned int vertexCount, Texture texture)
		: m_VaoID(vaoID), m_VertexCount(vertexCount), m_Texture(texture) {}

	inline GLuint VaoID() const { return m_VaoID; }
	inline unsigned int VertexCount() const { return m_VertexCount; }
	inline Texture GetTexture() const { return m_Texture; }

private:
	GLuint m_VaoID;
	unsigned int m_VertexCount;
	Texture m_Texture;
};