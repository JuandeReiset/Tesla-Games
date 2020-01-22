#pragma once

#include <string>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

// TODO: Model should be a component

/*
 * Class representing a drawable component in the game
 */
class Model
{
public:
	Model();
	// Loads the model from a given file name
	void LoadModel(std::string filename);
	// Loads the materials for the model and binds them as needed
	void LoadMaterials();
	// Clears model, freeing memory for other models to use
	void ClearModel();
	~Model();

private:
	// Loads a mesh node (How assimp loads objs)
	void LoadNode();

	// Mapping of meshes to their textures. Allows reusing textures
	std::vector<int> meshToTex;
	// List of all the meshes in the model
	std::vector<Mesh> meshList;
	// List of all the textures in the model
	std::vector<Texture> texList;
	// Shader used by the model
	Shader shader;
};

