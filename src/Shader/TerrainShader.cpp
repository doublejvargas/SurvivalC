#include "TerrainShader.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"

#include <fstream>
#include <sstream>

TerrainShader::TerrainShader(const std::string& filename)
{
	// Load shaders from file
	m_VertexShaderID = LoadShader(filename + ".vert", GL_VERTEX_SHADER);
	m_FragmentShaderID = LoadShader(filename + ".frag", GL_FRAGMENT_SHADER);

	// Create shader program
	GLCall(m_ProgramID = glCreateProgram());
	// Attach the shaders to the program
	GLCall(glAttachShader(m_ProgramID, m_VertexShaderID));
	GLCall(glAttachShader(m_ProgramID, m_FragmentShaderID));
	// Link the program
	GLCall(glLinkProgram(m_ProgramID));
	GLCall(glValidateProgram(m_ProgramID));

	// Check validation status
	GLint status;
	GLCall(glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &status));
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		GLCall(glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength));
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		GLCall(glGetProgramInfoLog(m_ProgramID, infoLogLength, NULL, infoLog));
		printf("ERROR: could not validate program \n%s\n", infoLog);
		// Delete the array
		delete[] infoLog;
	}

	BindAttributes();
	GetAllUniformLocations();
}

TerrainShader::~TerrainShader()
{
	GLCall(glDeleteProgram(m_ProgramID));
	printf("Deleted shaders\n");
}

void TerrainShader::Bind() const
{
	GLCall(glUseProgram(m_ProgramID));
}

void TerrainShader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void TerrainShader::BindAttributes()
{
	BindAttribute(0, "a_Position");
	BindAttribute(1, "a_TexCoord");
	BindAttribute(2, "a_TexIndex");
}

void TerrainShader::GetAllUniformLocations()
{
	m_TransformMatrixLoc = GetUniformLocation("u_TransformationMatrix");
	m_OrthoMatrixLoc = GetUniformLocation("u_ProjectionMatrix");
	m_ViewMatrixLoc = GetUniformLocation("u_ViewMatrix");
	m_TexturesLoc = GetUniformLocation("u_Textures");
}

GLuint TerrainShader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_ProgramID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}

void TerrainShader::BindAttribute(uint32_t layout_location, const std::string& name)
{
	GLCall(glBindAttribLocation(m_ProgramID, layout_location, name.c_str()));
}

void TerrainShader::LoadTransformMatrix(const glm::mat4& matrix)
{
	SetUniformMat4f(m_TransformMatrixLoc, matrix);
}

void TerrainShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	SetUniformMat4f(m_OrthoMatrixLoc, matrix);
}

void TerrainShader::LoadViewMatrix(Camera& camera)
{
	SetUniformMat4f(m_ViewMatrixLoc, CreateOrthoViewMatrix(camera));
}

void TerrainShader::LoadTextureSampler(const GLint* vec, uint32_t size)
{
	SetUniformVec1iv(m_TexturesLoc, size, vec);
}

void TerrainShader::SetUniformVec1iv(GLuint location, uint32_t size, const GLint* vec)
{
	GLCall(glUniform1iv(location, size, vec));
}

void TerrainShader::SetUniformVec3f(GLuint location, const glm::vec3& value)
{
	GLCall(glUniform3f(location, value.x, value.y, value.z));
}

void TerrainShader::SetUniformMat4f(GLuint location, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

glm::mat4 TerrainShader::CreateTransformationMatrix(const glm::vec2& translation, const glm::vec2& rotation, const glm::vec2& scale)
{
	// create translation matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation, 0.0f));
	// create rotation matrix
	glm::mat4 rotationMatrix =
		glm::rotate(glm::mat4(1.0f), 0.0f,		 glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0));
	// create scale matrix
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
	
	// the transformation matrix is the product of the three matrices above. Order matters: scale, rotate & translate (matrix multiplication is read from right to left!)
	return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 TerrainShader::CreateOrthoViewMatrix(Camera& camera)
{
	return glm::lookAt(camera.GetPosition(), camera.GetPosition() + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

GLuint TerrainShader::LoadShader(const std::string& filename, GLenum type)
{
	FILE* file;
	if (fopen_s(&file, filename.c_str(), "r") != 0)
	{
		printf("Failed to open: %s\n", filename.c_str());
		return -1;
	}

	std::string source;
	char buffer[1024], * token;
	while (fgets(buffer, 1024, file) != NULL)
	{
		source.append(buffer);
	}
	fclose(file);

	// Create shader id
	GLCall(GLuint id = glCreateShader(type));
	// Preparing source to load to OpenGL
	const GLchar* src = source.c_str();

	// Load source to OpenGL and compile
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));
	// Check compilation status
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		printf("Failed to compile %s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		GLCall(glDeleteShader(0));
		return 0;
	}

	return id;
}
