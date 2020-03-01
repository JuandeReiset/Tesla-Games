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

class PhysicsEngine
{
public:
	PhysicsEngine();
	void addEnemyVehicle(float x, float y, float z);	//add enemy vehicle at position (x,y,z)

	physx::PxVec3 GetBoxPos();
	void stepPhysics();
	int modeType = -1;
	int getModeType();
	void gearShift(float curSpeed);
	physx::PxRigidStatic* sphereActor = NULL;
	physx::PxRigidStatic* wallActor = NULL;
	Vehicle* player;
	std::vector<Vehicle*> enemyVehicles;


private:
	void cleanupPhysics();

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

