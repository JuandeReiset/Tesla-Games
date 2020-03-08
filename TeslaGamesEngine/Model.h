#pragma once

#include <string>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

#include "../include/PhysX/PxPhysicsAPI.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleSceneQuery.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleFilterShader.h"

using namespace physx;
using namespace snippetvehicle;

// TODO: Model should be a component

/*
 * Class representing a drawable component in the game
 */
class Model
{
public:
	Model();
	// Loads the model from a given file name
	void LoadModel(const std::string& fileName);
	// Loads the model from a given file name and a physics object, used for track cooking
	void LoadModel(const std::string& fileName, PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, bool isFloor);
	// Renders the model
	void RenderModel();
	// Clears model, freeing memory for other models to use
	void ClearModel();
	~Model();

private:
	void LoadNode(aiNode *node, const aiScene *scene);
	void LoadNode(aiNode* node, const aiScene* scene, PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, bool isFloor);	//for track cooking
	void LoadMesh(aiMesh *mesh, const aiScene *scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene, PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, bool isFloor);	//for track cooking
	void LoadMaterials(const aiScene *scene);

	std::vector<Mesh*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshToTex;
};

