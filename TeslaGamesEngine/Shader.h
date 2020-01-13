#pragma once

#include <string>

/*
 * Class handling loading of and applying shaders while rendering
 */
class Shader
{
public:
	Shader();
	// Loads a shader from a string of the code (useful for having a "base" shader
	void LoadFromString(std::string shaderCode);
	// Loads a shader from a specified file
	void LoadFromFile(std::string filename);
	// Uses the shader to render 
	void UseShader();
	// Clears the shader and frees memory
	void ClearShader();
	~Shader();

private:
	int shaderID;
};

