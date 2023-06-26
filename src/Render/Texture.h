#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(GLuint id) : m_TextureID(id) {}

	inline GLuint TextureID() { return m_TextureID; }

private:
	GLuint m_TextureID;
};