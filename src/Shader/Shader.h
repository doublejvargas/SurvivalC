#pragma once

#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include "glm/glm.hpp"


class Shader
{
private:
	// Necessary for creating, binding and unbinding
	unsigned int m_ProgramID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;
	
	//Uniform locations
	GLuint m_TransformMatrixLoc;
	GLuint m_OrthoMatrixLoc;

	// Uniform locations cache
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	inline GLuint ProgramID() { return m_ProgramID; }

	void BindAttributes();
	void GetAllUniformLocations();

	GLuint GetUniformLocation(const std::string& name);

	void BindAttribute(unsigned int layout_location, const std::string& name);

	void LoadTransformMatrix(const glm::mat4& matrix);
	void LoadOrthoMatrix(const glm::mat4& matrix);

	// May be useful for loading colors into shader
	void SetUniformVec3f(GLuint location, const glm::vec3& value);
	// Useful for loading othrographic (projection) matrix and transformation matrices into shader
	void SetUniformMat4f(GLuint location, const glm::mat4& matrix);

	//Helper methods
	static glm::mat4 CreateTransformationMatrix(const glm::vec2& translation, const glm::vec2& rotation, const glm::vec2& scale);

private:
	GLuint LoadShader(const std::string& filename, GLenum type);
};
