#include "pch.h"
#include "Model.h"

Model::Model()
{
}

void Model::RenderModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if (materialIndex < textureList.size() && textureList[materialIndex])
		{
			textureList[materialIndex]->UseTexture();
		}

		meshList[i]->RenderMesh();
	}
}

void Model::LoadModel(const std::string& fileName, PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, bool isFloor)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return;
	}

	LoadNode(scene->mRootNode, scene, gPhysics, gCooking, gMaterial, gScene, isFloor);

	LoadMaterials(scene);
}

void Model::LoadModel(const std::string & fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);
}

void Model::LoadNode(aiNode* node, const aiScene* scene, PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, bool isFloor)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene, gPhysics, gCooking, gMaterial, gScene, isFloor);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene, gPhysics, gCooking, gMaterial, gScene, isFloor);
	}
}

void Model::LoadNode(aiNode * node, const aiScene * scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

//used to cook the track mesh. This method automatically adds the track as actors to the scene!
void Model::LoadMesh(aiMesh* mesh, const aiScene* scene, PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, bool isFloor)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });	//loads actual positions
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
		
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//physx cooking here
	physx::PxTriangleMeshDesc meshDesc;

	//these vertices are 8 long, it goes x,y,z then texture x,y then normals x,y,z
	std::vector<PxVec3> actualVertices;
	for (int i = 0; i < mesh->mNumVertices; i++) {
		actualVertices.push_back(PxVec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
	}

	meshDesc.points.count = actualVertices.size();
	meshDesc.points.stride = sizeof(PxVec3);//needs a vector of 3 vertices
	meshDesc.points.data = reinterpret_cast<const void*>(actualVertices.data());

	meshDesc.triangles.count = indices.size()/3;
	meshDesc.triangles.stride = 3 * sizeof(GLfloat);//needs a vector of 3 vertices
	meshDesc.triangles.data = reinterpret_cast<const void*>(indices.data());


	
	PxTransform* trans = new PxTransform(PxVec3(0, -3.f, -1.5f));
	PxRigidStatic* rigidStat = gPhysics->createRigidStatic(*trans);

	if (isFloor) {	//make the shape a floor type
		PxFilterData groundPlaneSimFilterData(COLLISION_FLAG_GROUND, COLLISION_FLAG_GROUND_AGAINST, 0, 0);
		PxFilterData qFilterData;
		qFilterData.word3 = static_cast<PxU32>(DRIVABLE_SURFACE);

		PxDefaultMemoryOutputStream writeBuffer;
		PxTriangleMesh* triMesh;
		if (gCooking->cookTriangleMesh(meshDesc, writeBuffer)) {
			PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
			triMesh = gPhysics->createTriangleMesh(readBuffer);


			PxShape* shape = PxRigidActorExt::createExclusiveShape(*rigidStat, PxTriangleMeshGeometry(triMesh), *gMaterial);
			shape->setQueryFilterData(qFilterData);
			shape->setSimulationFilterData(groundPlaneSimFilterData);
			shape->setLocalPose(*trans);

			rigidStat = PxCreateStatic(*gPhysics, *trans, *shape);

			gScene->addActor(*rigidStat);	//add mesh to scene as actor
		}
		else {
			printf("\nTRACK COOKING FAILED!\n");
		}
	}
	else {	//make the shape an obstacle type
		PxFilterData obstFilterData(COLLISION_FLAG_OBSTACLE, COLLISION_FLAG_OBSTACLE_AGAINST, 0, 0);

		PxDefaultMemoryOutputStream writeBuffer;
		PxTriangleMesh* triMesh;
		if (gCooking->cookTriangleMesh(meshDesc, writeBuffer)) {
			PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
			triMesh = gPhysics->createTriangleMesh(readBuffer);

			PxShape* shape = PxRigidActorExt::createExclusiveShape(*rigidStat, PxTriangleMeshGeometry(triMesh), *gMaterial);
			shape->setSimulationFilterData(obstFilterData);
			shape->setLocalPose(*trans);

			rigidStat = PxCreateStatic(*gPhysics, *trans, *shape);


			gScene->addActor(*rigidStat);	//add mesh to scene as actor
		}
		else {
			printf("\nTRACK COOKING FAILED!\n");
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene * scene)
{
	textureList.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + filename;

				textureList[i] = new Texture(texPath.c_str());

				if (!textureList[i]->LoadTexture())
				{
					printf("Failed to load texture at: %s\n", texPath);
					delete textureList[i];
					textureList[i] = nullptr;
				}
			}
		}

		if (!textureList[i])
		{
			textureList[i] = new Texture("Textures/plain.png");
			textureList[i]->LoadTextureAlpha();
		}
	}
}

void Model::ClearModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < textureList.size(); i++)
	{
		if (textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
}

Model::~Model()
{
}
