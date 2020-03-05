#pragma once
#include <memory>
#include "Vehicle.h"
#include <vector>
#include "PhysX/include/PxPhysicsAPI.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleCreate.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleSceneQuery.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleFilterShader.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleTireFriction.h"
#include "PhysX/vehicle4W/snippetcommon/SnippetPVD.h"
#include "PhysX/include/vehicle/PxVehicleUtil.h"
#include "PhysX/include/snippetutils/SnippetUtils.h"
#include "audioEngine.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	void initAudioForVehicles(AudioEngine * audio);
	void addEnemyVehicle(float x, float y, float z);	//add enemy vehicle at position (x,y,z)

	physx::PxVec3 GetBoxPos();
	void stepPhysics();
	int modeType = -1;
	int getModeType();
	void gearShift(float curSpeed);
	physx::PxRigidStatic* sphereActor = NULL;
	physx::PxRigidStatic* wallActor = NULL;
	//std::unique_ptr<Vehicle> player;
	Vehicle* player;	//the player vehicle
	std::vector<Vehicle*> enemyVehicles;	//the AI vehicles

	void update_dir_render4Vehicle(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float Dir_x, float Dir_y, float Dir_z);


private:
	void cleanupPhysics();
	AudioEngine* audioEngine;

	physx::PxDefaultAllocator gAllocator;
	physx::PxDefaultErrorCallback gErrorCallback;

	physx::PxFoundation* gFoundation = NULL;
	physx::PxPhysics* gPhysics = NULL;
	physx::PxDefaultCpuDispatcher* gDispatcher = NULL;
	physx::PxScene* gScene = NULL;
	physx::PxMaterial* gMaterial = NULL;
	physx::PxCudaContextManager* gCudaContextManager = NULL;
	physx::PxRigidDynamic* ball = NULL;
	physx::PxF32 gVehicleModeLifetime = 4.0f;
	physx::PxF32 gVehicleModeTimer = 0.0f;
	physx::PxU32 gVehicleOrderProgress = 0;
	bool gVehicleOrderComplete = false;
	bool gMimicKeyInputs = false;
	physx::PxRigidStatic* gGroundPlane = NULL;
	
	physx::PxRigidStatic* box = NULL;
	physx::PxShape* shape = NULL;
	physx::PxCooking* gCooking = NULL;

	physx::PxPvd* gPvd = NULL;
};

