#pragma once
#include <memory>
#include <list>
#include <vector>

#include "PhysX/include/PxSimulationEventCallback.h"
#include "HealthComponent.h"
#include "ShootComp.h"
#include "Global.h"
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
#include "Caltrops.h"
#include "Smoke.h"
#include "Oil.h"
#include "LapMarker.h"

//#include "Bullet.h"
#include "TrackDrivingPoint.h"

using namespace physx;

/*
 * Vehicle class inherits from Object class, with values like health, speed, etc.
 */
class Vehicle : public Object
{
public:
	std::vector<LapMarker*>* lapMarkers;

	Vehicle(PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, PxDefaultAllocator gAllocator, float x, float y, float z, int id, std::vector<LapMarker*>* markers);	//added id to this
	Vehicle(int id);//pls dont use this
	~Vehicle();
	void update(physx::PxF32 timestep, PxScene* gScene);

	int ID;

	//lap position stuff
	int totalMarkersHit;
	int numberOfMarkersInTrack;
	float distance;
	void updateDistance();

	//lap components
	bool isPlayer;
	int currentMarker;
	int expectedMarker;
	int numLaps;
	void hitLapMarker(int val, int trackTotalLaps);
	void lapWinCondition();

	void initAITrackPoints(std::vector<std::unique_ptr<TrackDrivingPoint>>* listOfPoints);
	void incrementAITrackPoint();
	TrackDrivingPoint pastTarget;
	TrackDrivingPoint curTarget;
	int trackPointListIndex;
	bool isAICar;
	bool isAICarStuck = false;
	int AICarStuckFrameCounter = 0;
	int AICarStuckMoveCounter = 0;
	TrackDrivingPoint oldStuckTarget = TrackDrivingPoint(0,0,0,-1);



	//ability stuff
	int ability;


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

	void handbrakeTurn(float magnitudeBrake, float magnitudeTurn);

	void handleSound();
	float previousSpeed = 0.f;
	float previousAccel = 0.f;
	int speedFrameIndex = 0;

	float GetRotationAngle();
	physx::PxVec3 GetPosition();
	physx::PxTransform GetTransform();

	float GetForwardsSpeed();

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
	void takeTrapDamage(double dmgAmount);
	void takeBulletDamage(double dmgAmount);									//get damage for damaging object
	void firelazer();

	void pickup();													//pick up a(n) item/ability
	//ammo pickup, increases ammo by 1 to a max of 10
	void ammo();

	//pls add your ability stuff here
	void useCaltrops(std::list<Caltrops*> *caltropsList, float duration);
	void useSmoke(std::list<Smoke*> *smokeList, float duration);
	void useOil(std::list<Oil*> *oilList, float duration);

	bool affectedBySmoke;
	float smokeStartTime, smokeDuration;
	void enableSmokeEffect();
	void disableSmokeEffect();
	void updateSmoke();

	bool affectedByOil;
	float oilStartTime, oilDuration;
	void enableOilEffect();
	void disableOilEffect();
	void updateOil();

	float currentTime;
	void updateCurrentTime();

private:
	HealthComponent health = HealthComponent(100);
	ShootComp turret = ShootComp();
	

	AudioEngine* audioEngine;
	AudioBoomBox accelerateFromRest;
	AudioBoomBox accelerateFromMotion;
	AudioBoomBox maxSpeed;
	AudioBoomBox boostStart;
	AudioBoomBox boostMax;
	AudioBoomBox deployCaltropsEffect;
	AudioBoomBox deployOilEffect;
	AudioBoomBox deploySmokeEffect;

	std::vector<std::unique_ptr<TrackDrivingPoint>>* listOfPoints;

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
	void releaseAllControls();//each vihecle has a unique number for recognizition

};

