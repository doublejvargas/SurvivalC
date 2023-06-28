#pragma once

#include "Texture.h"

class Model
{
public:
	Model(GLuint vaoID, unsigned int vertexCount, Texture texture)
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
	inline unsigned int VertexCount() const { return m_VertexCount; }
	inline Texture GetTexture() const { return m_Texture; }

private:
	GLuint m_VaoID;
	unsigned int m_VertexCount;
	Texture m_Texture;
};