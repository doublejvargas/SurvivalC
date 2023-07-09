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
		: m_VaoID(m.VaoID()), m_VertexCount(m.vertexCount()), m_Texture(m.getTexture()) {}

	void operator=(const Model& m)
	{
		m_VaoID = m.VaoID();
		m_VertexCount = m.vertexCount();
		m_Texture = m.getTexture();
	}

	inline GLuint VaoID() const					{ return m_VaoID; }
	inline uint32_t vertexCount() const			{ return m_VertexCount; }
	inline Texture getTexture() const			{ return m_Texture; }
	
	inline void setTexture(const Texture& t)	{ m_Texture = t; }

	bool operator==(const Model& M) const
	{
		if (M.VaoID() == m_VaoID) {
			if (M.vertexCount() == m_VertexCount) {
				if (M.getTexture() == m_Texture)
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
			^ (std::hash<uint32_t>()(model.vertexCount()) << 1)) >> 1)
			^ (std::hash<uint32_t>()(model.getTexture().TextureID()) << 1);
	}
};
