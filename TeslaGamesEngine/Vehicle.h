#pragma once

#include "PhysX/include/PxSimulationEventCallback.h"
#include "HealthComponent.h"
#include "ShootComp.h"
#include "Global.h"
#include <memory>
#include "../include/PhysX/PxPhysicsAPI.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleCreate.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleSceneQuery.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleFilterShader.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleTireFriction.h"
#include "PhysX/vehicle4W/snippetcommon/SnippetPVD.h"
#include "PhysX/include/vehicle/PxVehicleUtil.h"
#include "PhysX/include/snippetutils/SnippetUtils.h"
#include "Object.h"
#include "audioEngine.h"

//#include "Bullet.h"

using namespace physx;

/*
 * Vehicle class inherits from Object class, with values like health, speed, etc.
 */
class Vehicle : public Object
{
public:
	Vehicle(bool isPlayerCheck, PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, PxDefaultAllocator gAllocator, float x, float y, float z);
	Vehicle(int id);//pls dont use this
	~Vehicle();
	void update(physx::PxF32 timestep, PxScene* gScene);

	//lap components
	bool isPlayer;
	int currentMarker;
	int expectedMarker;
	int numLaps;
	void hitLapMarker(int val, int trackTotalLaps, int trackTotalLapMarkers);
	void lapWinCondition();
  
	//Shooting component functions
	void update_turret();
	void shoot(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float x, float y, float z);
	void renderBullets();
	ShootComp* getShootingComponent();

	//Health Component functions
	void update_health();
	HealthComponent* getHealthComponent();

	void cleanup();
	void audioUpdate();
	void initVehicle(PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, PxDefaultAllocator gAllocator, PxVec3 position);
	void initVehicleAudio(AudioEngine * engine);
	//controls
	void forwards(float magnitude);
	void reverse(float magnitude);
	void turn(float magnitude);
	void cleanupPhysics(PxDefaultAllocator gAllocator);

	void gearShift(float curSpeed);

	void handleSound();
	float previousSpeed = 0.f;
	float previousAccel = 0.f;
	int speedFrameIndex = 0;

	float GetRotationAngle();
	physx::PxVec3 GetPosition();
	physx::PxTransform GetTransform();



	PxRigidDynamic* actor;

	bool collidingWithVolume = false;

	//physx vehicle stuff
	physx::PxVehicleDrive4W* gVehicle4W = NULL;

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
	
	void Tick(float deltaTime);
	double currentHealth();											//get the current health
	void getDamage(double damage);									//get damage for damaging object
	void firelazer();
private:
	HealthComponent health = HealthComponent(100);
	ShootComp turret = ShootComp();
	int ID;

	AudioEngine* audioEngine;
	AudioBoomBox accelerateFromRest;
	AudioBoomBox accelerateFromMotion;
	AudioBoomBox maxSpeed;
	AudioBoomBox boostStart;
	AudioBoomBox boostMax;

	
	physx::PxF32 gSteerVsForwardSpeedData[2 * 8];
	bool gIsVehicleInAir = true;
	physx::PxFixedSizeLookupTable<8> gSteerVsForwardSpeedTable;

	DriveMode gDriveModeOrder[8];

	physx::PxVehicleKeySmoothingData gKeySmoothingData;
	physx::PxVehiclePadSmoothingData gPadSmoothingData;

	snippetvehicle::VehicleSceneQueryData* gVehicleSceneQueryData = NULL;
	physx::PxBatchQuery* gBatchQuery = NULL;
	physx::PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL;
	physx::PxVehicleDrive4WRawInputData gVehicleInputData;

	physx::PxF32 gVehicleModeLifetime = 4.0f;
	physx::PxF32 gVehicleModeTimer = 0.0f;
	physx::PxU32 gVehicleOrderProgress = 0;
	bool gVehicleOrderComplete = false;
	bool gMimicKeyInputs = false;				//I think this is for keyboard controls to mimic a controller analog scheme, keep it in for now....	

	snippetvehicle::VehicleDesc initVehicleDesc(PxMaterial* gMaterial);
	void keyPress(unsigned char key, const physx::PxTransform& camera);
	void startHandbrakeTurnLeftMode(float magnitude);
	void startHandbrakeTurnRightMode(float magnitude);
	void releaseAllControls();//each vihecle has a unique number for recognizition

	
	/*
	For sound synch we need a way to track the vehicle speed and acceleration states so they can
	alert us to the following events

		- Accelerating from rest/0 speed
		- Accelerating from motion/non-zero speed
		- When vehicle hits the max speed
		- When the vehicle activates boost and is not at max speed
		- When the vehicle activates boost and is at max speed


	*/


};

