#pragma once
#include <memory>
#include "PhysX/PxPhysicsAPI.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleCreate.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleSceneQuery.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleFilterShader.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleTireFriction.h"
#include "PhysX/vehicle4W/snippetcommon/SnippetPVD.h"
#include "PhysX/vehicle/PxVehicleUtil.h"
#include "PhysX/snippetutils/SnippetUtils.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	//~PhysicsEngine();
	physx::PxVec3 GetPosition();
	physx::PxVec3 GetBoxPos();
	float GetRotationAngle();
	void stepPhysics();
	int modeType = -1;
	int getModeType();
	void increaseForwards();
	void upwards();
	void forwards(float magnitude);
	void reverse(float magnitude);
	void turnLeft(float magnitude);
	void turnRight(float magnitude);
	void brake();
	void turn(float magnitude);
	physx::PxVehicleDrive4W* gVehicle4W = NULL;
	physx::PxRigidDynamic *getVehicleRigidDynamicPtr();
	physx::PxRigidStatic* sphereActor = NULL;
	physx::PxRigidStatic* wallActor = NULL;

	

	enum DriveMode
	{
		eDRIVE_MODE_ACCEL_FORWARDS = 0,
		eDRIVE_MODE_ACCEL_REVERSE,
		eDRIVE_MODE_HARD_TURN_LEFT,
		eDRIVE_MODE_HANDBRAKE_TURN_LEFT,
		eDRIVE_MODE_HARD_TURN_RIGHT,
		eDRIVE_MODE_HANDBRAKE_TURN_RIGHT,
		eDRIVE_MODE_BRAKE,
		eDRIVE_MODE_NONE
	};
private:
	//physx::PxRigidDynamic* CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity);
	snippetvehicle::VehicleDesc initVehicleDesc();
	void initVehicle();
	void startBrakeMode();
	void keyPress(unsigned char key, const physx::PxTransform& camera);
	void startAccelerateForwardsMode(float magnitude);
	void startAccelerateReverseMode(float magnitude);
	void startTurnHardLeftMode(float magnitude);
	void startTurnHardRightMode(float magnitude);
	void startHandbrakeTurnLeftMode(float magnitude);
	void startHandbrakeTurnRightMode(float magnitude);
	void releaseAllControls();
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
	snippetvehicle::VehicleSceneQueryData* gVehicleSceneQueryData = NULL;
	physx::PxBatchQuery* gBatchQuery = NULL;
	physx::PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL;
	physx::PxVehicleDrive4WRawInputData gVehicleInputData;


	physx::PxF32 gSteerVsForwardSpeedData[2 * 8];
	bool gIsVehicleInAir = true;
	physx::PxFixedSizeLookupTable<8> gSteerVsForwardSpeedTable;

	DriveMode gDriveModeOrder[8];

	physx::PxVehicleKeySmoothingData gKeySmoothingData;
	physx::PxVehiclePadSmoothingData gPadSmoothingData;
};

