#pragma once

#include "Texture.h"
#include <stdio.h> //NULL
#include <functional>

typedef unsigned int uint32_t;

class Model
{
public:
	Model() : m_VaoID(0), m_VertexCount(0) { }

	Model(GLuint vaoID, uint32_t vertexCount, const Texture& texture = NULL)
		: m_VaoID(vaoID), m_VertexCount(vertexCount), m_Texture(texture) {}

	Model(const Model& m)
		: m_VaoID(m.VaoID()), m_VertexCount(m.VertexCount()), m_Texture(m.GetTexture()) {}

	void operator=(const Model& m)
	{
		m_VaoID = m.VaoID();
		m_VertexCount = m.VertexCount();
		m_Texture = m.GetTexture();
	}

	inline GLuint VaoID() const { return m_VaoID; }
	inline uint32_t VertexCount() const { return m_VertexCount; }
	inline Texture GetTexture() const { return m_Texture; }

	bool operator==(const Model& M) const
	{
		if (M.VaoID() == m_VaoID) {
			if (M.VertexCount() == m_VertexCount) {
				if (M.GetTexture() == m_Texture)
					return true;
			}
		}

		return false;
	}

private:
	GLuint m_VaoID;
	uint32_t m_VertexCount;
	Texture m_Texture;
};


// This specialization of std::hash is done with the purpose of allowing the use of Model as
//  a key in an unordered_map. This is required for MasterRenderer class "ProcessEntity" function.
template <>
struct std::hash<Model>
{
	size_t operator()(const Model& model) const
	{
		return ((std::hash<uint32_t>()(model.VaoID())
			^ (std::hash<uint32_t>()(model.VertexCount()) << 1)) >> 1)
			^ (std::hash<uint32_t>()(model.GetTexture().TextureID()) << 1);
	}
};
