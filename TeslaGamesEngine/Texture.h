#pragma once

#include <string>

/*
 * Class for loading and using textures in OpenGL
 */
class Texture
{
public:
	Texture();
	// Loads a texture with NO alpha channels
	void LoadTexture();
	// Loads a texture with alpha channels
	void LoadTextureAlpha();
	~Texture();

private:
	int width;
	int height;
	int bitdepth;

	std::string fileLocation;
};

