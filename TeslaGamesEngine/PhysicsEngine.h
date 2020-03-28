#pragma once
#include <memory>
#include <algorithm>
#include "Vehicle.h"
#include "LapMarker.h"
#include "PickupBox.h"
#include "Caltrops.h"
#include "Smoke.h"
#include "Oil.h"
#include "ColliderCallback.h"
#include <vector>
#include <list>
#include "PhysX/include/PxPhysicsAPI.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleCreate.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleSceneQuery.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleFilterShader.h"
#include "PhysX/vehicle4W/snippetvehiclecommon/SnippetVehicleTireFriction.h"
#include "PhysX/vehicle4W/snippetcommon/SnippetPVD.h"
#include "PhysX/include/vehicle/PxVehicleUtil.h"
#include "PhysX/include/snippetutils/SnippetUtils.h"
#include "../include/PhysX/PxSimulationEventCallback.h"
#include <string>
#include "audioEngine.h"
#include "Track.h"

class PhysicsEngine
{
	//sorts the vehicles list by a custom set of rules for position
	struct VehicleComparator {
		bool operator()(Vehicle* v1, Vehicle* v2) {
			if (v1->totalMarkersHit > v2->totalMarkersHit) {
				return true;	
			} 
			else if (v1->totalMarkersHit == v2->totalMarkersHit) {
				if (v1->distance <= v2->distance) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;	//v2 is "smaller" so better
			}
		}
	};


public:
	//super hacky im sorry
	const std::string VEHICLE = "vehicle";
	const std::string PICKUP = "pickup";
	const std::string LAPMARKER = "lapmarker";
	const std::string CALTROPS = "caltrops";
	const std::string SMOKE = "smoke";
	const std::string OIL = "oil";

	PhysicsEngine();
	void initAudioForVehicles(AudioEngine * audio);

	void initAITrack(Track * raceTrack);
	void addPlayerVehicle(int startIndex);
	void addEnemyVehicle(int startIndex);
	

	physx::PxVec3 GetBoxPos();
	void stepPhysics();
	int modeType = -1;
	int getModeType();

	physx::PxRigidStatic* sphereActor = NULL;
	physx::PxRigidStatic* wallActor = NULL;

	std::vector<Vehicle*> playerVehicles;
	// Vehicle* player;	//the player vehicle
	std::vector<Vehicle*> enemyVehicles;	//the AI vehicles
	std::vector<LapMarker*> lapmarkers;		//the lap markers
	std::list<PickupBox*> pickupBoxes;	//the pickup boxes
	std::list<Caltrops*> caltropsList;
	std::list<Smoke*> smokeList;
	std::list<Oil*> oilList;

	std::vector<Vehicle*> allVehicles;
	void sortVehicles();

	PxRigidActor* testActor;

	ColliderCallback* colliderCallback;


	void createPickupTriggerVolume(float x, float y, float z);
	void createLapMarkerTriggerVolume(int lapMarkerValue, PxVec3 position, PxVec3 dimensions);
	void createCaltropsTriggerVolume(float x, float y, float z, float duration, int player);
	void createSmokeTriggerVolume(float x, float y, float z, float duration, int player);
	void createOilTriggerVolume(float x, float y, float z, float duration, int player);


	void update_dir_render4Vehicle(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float Dir_x, float Dir_y, float Dir_z);

	physx::PxPhysics* gPhysics = NULL;
	physx::PxScene* gScene = NULL;
	physx::PxMaterial* gMaterial = NULL;

	physx::PxCooking* gCooking = NULL;

	void loadLapMarkers();

	void setTrack(Track* t);

private:
	void cleanupPhysics();
	AudioEngine* audioEngine;
	Track* raceTrack;

	physx::PxDefaultAllocator gAllocator;
	physx::PxDefaultErrorCallback gErrorCallback;
	physx::PxFoundation* gFoundation = NULL;
	physx::PxDefaultCpuDispatcher* gDispatcher = NULL;
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
	physx::PxPvd* gPvd = NULL;
};

