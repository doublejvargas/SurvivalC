#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture() : m_TextureID(0) {}
	Texture(GLuint id) : m_TextureID(id) {}
	Texture(const Texture& t) : m_TextureID(t.TextureID()) {}

	inline GLuint TextureID() const { return m_TextureID; }

	bool operator==(const Texture& T) const
	{
		return (T.TextureID() == m_TextureID);
	}

private:
	GLuint m_TextureID;
};