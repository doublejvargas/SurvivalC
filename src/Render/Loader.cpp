#include "Loader.h"
#include "Log.h"
#include <cassert>
#include "stb_image/stb_image.h"

Loader::Loader()
{
	m_VAOS.clear();
	m_VBOS.clear();
	m_IBOS.clear();
	m_Textures.clear();
}

Loader::~Loader()
{
	// Loop through all the storage arrays and delete OpenGL variables.
	// This destructor is VERY important as it destroys ALL of the models OpenGL will be drawing once we are done.
	// "done" here means that function containing loader object exits out of scope. More specifically, it would be ApplicationManager::Start() in this application's case.
	while (m_VAOS.size() > 0)
	{
		GLCall(glDeleteVertexArrays(1, &m_VAOS.back()));
		m_VAOS.pop_back();
	}
	while (m_VBOS.size() > 0)
	{
		GLCall(glDeleteBuffers(1, &m_VBOS.back()));
		m_VBOS.pop_back();
	}
	while (m_IBOS.size() > 0)
	{
		GLCall(glDeleteBuffers(1, &m_IBOS.back()));
		m_IBOS.pop_back();
	}
	while (m_Textures.size() > 0)
	{
		GLCall(glDeleteTextures(1, &m_Textures.back()));
		m_Textures.pop_back();
	}

	printf("Cleared array objects, buffers and textures\n");
}

Model Loader::LoadToVAO(const std::vector<float>& positions, const std::vector<float>& texCoords,
	const std::vector<unsigned int>& indices, const std::string& filename)
{
	// Create a new VAO
	GLuint vaoID = CreateVAO();
	BindIndicesBuffer(indices.data(), indices.size());
	// positions in layout location/attrib location 0
	StoreDataInAttributeList(0, 2, positions.size() * sizeof(float), GL_FLOAT, positions.data());
	// texture coordinates in layout location/attrib location 1
	StoreDataInAttributeList(1, 2, texCoords.size() * sizeof(float), GL_FLOAT, texCoords.data());

	UnbindVAO();
	// Look at console for any errors loading texture! That or Assert texture.
	return Model(vaoID, indices.size(), LoadTexture(filename));
}

GLuint Loader::LoadTexture(const std::string& path)
{
	GLuint id;
	int width, height, bpp;
	// Load image data
	unsigned char* databuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
	if (!databuffer)
	{
		std::cerr << "ERROR: texture loading failed for: " << path << std::endl;
		return -1;
	}
	// Generate and bind a OpenGL texture
	GLCall(glGenTextures(1, &id));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
	// Tell OpenGL how to fill an area that's too big or too small
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// Tell OpenGL to clamp textures to edge (so you don't get transparent gaps) OR we can use GL_REPEAT for tiling
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	// Store the OpenGL texture data
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, databuffer));
	// Unbind texture
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	// Store the buffer in the list
	m_Textures.push_back(id);
	// Unload image data
	stbi_image_free(databuffer);

	return id;
}

void Loader::UnbindVAO() const
{
	GLCall(glBindVertexArray(0));
}

GLuint Loader::CreateVAO()
{
	GLuint vaoID;
	// Create a new VAO
	GLCall(glGenVertexArrays(1, &vaoID));
	// Store the VAO in our local list
	m_VAOS.push_back(vaoID);
	// Bind the VAO to use it
	GLCall(glBindVertexArray(vaoID));

	return vaoID;
}

void Loader::StoreDataInAttributeList(GLuint layoutloc, unsigned int dimension, unsigned int bytesize, GLenum type, const void* data)
{
	GLuint vboID;
	// Create new buffer
	GLCall(glGenBuffers(1, &vboID));
	// Store the buffer in our local list
	m_VBOS.push_back(vboID);
	// Bind the buffer to use it
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	// Store the data in the buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, bytesize, data, GL_STATIC_DRAW));
	// Tell OpenGL how and where to store this VBO in the VAO
	GLCall(glVertexAttribPointer(layoutloc, dimension, type, GL_FALSE, 0, nullptr));
}

void Loader::BindIndicesBuffer(const unsigned int* indices, unsigned int count)
{
	GLuint iboID;
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	// Generate buffer and bind for use
	GLCall(glGenBuffers(1, &iboID));
	// Store in our local list
	m_IBOS.push_back(iboID);
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
	// Store the data in the buffer in OpenGL/ GPU
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

