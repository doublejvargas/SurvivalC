#pragma once

#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include "glm/glm.hpp"
#include "Camera.h"


class TerrainShader
{
private:
	// Necessary for creating, binding and unbinding
	uint32_t m_ProgramID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;
	
	//Uniform locations
	GLuint m_TransformMatrixLoc;
	GLuint m_OrthoMatrixLoc;
	GLuint m_ViewMatrixLoc;
	GLuint m_TexturesLoc;

	// Uniform locations cache
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	TerrainShader(const std::string& filename);
	~TerrainShader();

	void Bind() const;
	void Unbind() const;

	inline GLuint ProgramID() { return m_ProgramID; }

	void BindAttributes();
	void GetAllUniformLocations();

	GLuint GetUniformLocation(const std::string& name);

	void BindAttribute(uint32_t layout_location, const std::string& name);

	void LoadTransformMatrix(const glm::mat4& matrix);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadTextureSampler(const GLint* vec, uint32_t size);

	void SetUniformVec1iv(GLuint location, uint32_t size, const GLint* vec);
	// May be useful for loading colors into shader
	void SetUniformVec3f(GLuint location, const glm::vec3& value);
	// Useful for loading orthographic (projection) matrix and transformation matrices into shader
	void SetUniformMat4f(GLuint location, const glm::mat4& matrix);

	//Helper methods
	static glm::mat4 CreateTransformationMatrix(const glm::vec2& translation, const glm::vec2& rotation, const glm::vec2& scale);
	static glm::mat4 CreateOrthoViewMatrix(Camera& camera);

private:
	GLuint LoadShader(const std::string& filename, GLenum type);
};
