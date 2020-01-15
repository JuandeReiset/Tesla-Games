#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

/*
 * Class responsible for loading shaders and aplpying them during rendering
 */
class Shader
{
public:
	Shader();

	// Create a shader from hard coded functions
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	// Load a shader from provided files
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	// Helper method for file IO
	std::string ReadFile(const char* fileLocation);

	// Accessors for applying uniform locations to the shader
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	// Use the shader in rendering
	void UseShader();
	// Clear the shader from memory + free the memory
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel;

	// Helper method for converting shader string to executable code
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	// Helper method to add a shader to the shader program
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

