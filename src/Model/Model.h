#pragma once

#include "Texture.h"
#include <stdio.h> //NULL

typedef unsigned int uint32_t;

class Model
{
public:
	Model(GLuint vaoID, uint32_t vertexCount, const Texture& texture = NULL)
		: m_VaoID(vaoID), m_VertexCount(vertexCount), m_Texture(texture) {}

	Model(const Model& m)
		: m_VaoID(m.VaoID()), m_VertexCount(m.VertexCount()), m_Texture(m.GetTexture()) {}

	Model& operator=(const Model& m)
	{
		m_VaoID = m.VaoID();
		m_VertexCount = m.VertexCount();
		m_Texture = m.GetTexture();
	}

	inline GLuint VaoID() const { return m_VaoID; }
	inline uint32_t VertexCount() const { return m_VertexCount; }
	inline Texture GetTexture() const { return m_Texture; }

private:
	GLuint m_VaoID;
	uint32_t m_VertexCount;
	Texture m_Texture;
};