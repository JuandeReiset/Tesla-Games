#include "PhysicsEngine.h"
#include <ctype.h>
#include <iostream>

#include "../include/PhysX/PxPhysicsAPI.h"


#include "../include/PhysX/vehicle/PxVehicleUtil.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleSceneQuery.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleFilterShader.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleTireFriction.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleCreate.h"

#include "../TeslaGamesEngine/snippetcommon/SnippetPrint.h"
#include "../TeslaGamesEngine/snippetcommon/SnippetPVD.h"
#include "../TeslaGamesEngine/snippetutils/SnippetUtils.h"


using namespace physx;
using namespace snippetvehicle;



PhysicsEngine::PhysicsEngine() {
	std::cout << "\nGOT TO PHYSENGG CONSTRUCTOR\n";
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	//set physics
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);


	//set scene
	sceneDesc = new PxSceneDesc(gPhysics->getTolerancesScale());
	sceneDesc->gravity = PxVec3(0.0f, -9.81f, 0.0f);

	//cpu worker thread setup and add to sceneDesc
	PxU32 numWorkers = 1;
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	sceneDesc->cpuDispatcher = gDispatcher;
	sceneDesc->filterShader = VehicleFilterShader;

	//creates the collider event handler needed for trigger volumes and adds to scene
	colliderCallback = new ColliderCallback();
	sceneDesc->simulationEventCallback = colliderCallback;

	gScene = gPhysics->createScene(*sceneDesc);

	PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));

	player = new Vehicle(gPhysics, gCooking, gMaterial, gScene, gAllocator, 0, 5, 0);

	//create obstacle (needed for now)
	PxFilterData obstFilterData(snippetvehicle::COLLISION_FLAG_OBSTACLE, snippetvehicle::COLLISION_FLAG_OBSTACLE_AGAINST, 0, 0);
	PxShape* boxwall = gPhysics->createShape(PxBoxGeometry(1.0f, 2.0f, 1.0f), *gMaterial, false);
	wallActor = gPhysics->createRigidStatic(PxTransform(PxVec3(0, 0, 0)));
	boxwall->setSimulationFilterData(obstFilterData);
	wallActor->setGlobalPose(PxTransform(PxVec3(0, 2, 5)));
	wallActor->attachShape(*boxwall);
	//gScene->addActor(*wallActor);

	createTriggerVolume(0, 6.f, 0);

	//Create a plane to drive on (once we get track cooking working we can remove this, or have this as a safeguard just in case)
	PxFilterData groundPlaneSimFilterData(COLLISION_FLAG_GROUND, COLLISION_FLAG_GROUND_AGAINST, 0, 0);
	gGroundPlane = createDrivablePlane(groundPlaneSimFilterData, gMaterial, gPhysics);
	gScene->addActor(*gGroundPlane);

	
}

/*
Make class that extends xsimeventcalback
set simevent callback to instance of the above in the gScene




*/


void PhysicsEngine::addEnemyVehicle(float x, float y, float z)
{
	//create vehicle object
	//add it to the list of vehicle
	Vehicle* v = new Vehicle(gPhysics, gCooking, gMaterial, gScene, gAllocator, x, y, z);
	enemyVehicles.push_back(v);
}

physx::PxVec3 PhysicsEngine::GetBoxPos()
{
	return wallActor->getGlobalPose().p;
}

void PhysicsEngine::stepPhysics()
{
	const PxF32 timestep = 1.0f / 60.0f;

	player->update(timestep, gScene);

	if (!enemyVehicles.empty()) {
		for (int i = 0; i < enemyVehicles.size(); i++) {
			enemyVehicles.at(i)->update(timestep, gScene);
		}
	}

	//Scene update.
	gScene->simulate(timestep);
	gScene->fetchResults(true);
}

int PhysicsEngine::getModeType()
{
	return modeType;
}

//creates a trigger colume at point (x,y,z) and adds it to the scene
void PhysicsEngine::createTriggerVolume(float x, float y, float z)
{
	PxBoxGeometry geometry(5.f, 5.f, 5.f);
	PxTransform transform(PxVec3(x,y,z));
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);

	PxShape* shape;

	actor->getShapes(&shape, 1);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	gScene->addActor(*actor);
	std::cout << "\nADDED ACTOR TO SCENE\n";
}


void PhysicsEngine::cleanupPhysics()
{
	player->cleanupPhysics(gAllocator);

	if (!enemyVehicles.empty()) {
		for (int i = 0; i < enemyVehicles.size(); i++) {
			enemyVehicles.at(i)->cleanupPhysics(gAllocator);
		}
	}


	box->release();
	PX_RELEASE(gGroundPlane);
	
	PX_RELEASE(gMaterial);
	PX_RELEASE(gCooking);
	PX_RELEASE(gScene);
	PX_RELEASE(gDispatcher);
	PX_RELEASE(gPhysics);
	if (gPvd)
	{
		PxPvdTransport* transport = gPvd->getTransport();
		gPvd->release();	gPvd = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(gFoundation);

	printf("SnippetVehicle4W done.\n");
}

