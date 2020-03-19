#include "PhysicsEngine.h"
#include <ctype.h>
#include <iostream>


#include "../TeslaGamesEngine/snippetcommon/SnippetPrint.h"


using namespace physx;
using namespace snippetvehicle;

PhysicsEngine::PhysicsEngine() {
	std::cout << "\nGOT TO PHYSENGG CONSTRUCTOR\n";
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	//set physics
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);


	//set scene
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	PxU32 numWorkers = 1;
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = VehicleFilterShader;

	//creates the collider event handler needed for trigger volumes and adds to scene
	colliderCallback = new ColliderCallback();
	sceneDesc.simulationEventCallback = colliderCallback;
	

	gScene = gPhysics->createScene(sceneDesc);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));

	player = new Vehicle(true, gPhysics, gCooking, gMaterial, gScene, gAllocator, 70, 5, -86, 1);
	player->actor->userData = player;

	//create obstacle (needed for now)
	PxFilterData obstFilterData(snippetvehicle::COLLISION_FLAG_OBSTACLE, snippetvehicle::COLLISION_FLAG_OBSTACLE_AGAINST, 0, 0);
	PxShape* boxwall = gPhysics->createShape(PxBoxGeometry(1.0f, 2.0f, 1.0f), *gMaterial, false);
	wallActor = gPhysics->createRigidStatic(PxTransform(PxVec3(0, 0, 0)));
	boxwall->setSimulationFilterData(obstFilterData);
	wallActor->setGlobalPose(PxTransform(PxVec3(0, 2, 5)));
	wallActor->attachShape(*boxwall);
	//gScene->addActor(*wallActor);

	//createPickupTriggerVolume(0, 0, 0, 2, 2, 2);
	createPickupTriggerVolume(0, 2, 10, 2, 2, 2);
	createPickupTriggerVolume(2, 2, 10, 2, 2, 2);
	//createPickupTriggerVolume(33, 1, -87, 4, 2, 1.65f);	//these sizes and the render scale values make a nice box size

	//new lap markers
	createLapMarkerTriggerVolume(0, 70, 2, -86, 4, 10, 30);			//0, start/finish position
	createLapMarkerTriggerVolume(1, -76, 2, -85, 11, 10, 30);		//1
	createLapMarkerTriggerVolume(2, -100, 2, -45, 30, 10, 6);		//2
	createLapMarkerTriggerVolume(3, -85, 2, 39, 26, 10, 15);		//3
	createLapMarkerTriggerVolume(4, -55, 2, 51, 17, 10, 20);		//4
	createLapMarkerTriggerVolume(5, -7, 2, 5, 6, 10, 31);			//5
	createLapMarkerTriggerVolume(6, 23, 2, 36, 19, 10, 19);			//6
	createLapMarkerTriggerVolume(7, 105.3f, 2, 53, 5, 10, 30);		//7
	createLapMarkerTriggerVolume(8, 212, 2, 33, 10, 10, 23);		//8
	createLapMarkerTriggerVolume(9, 215, 2, -2, 28, 10, 7);			//9
	createLapMarkerTriggerVolume(10, 225.5f, 2, -58, 30, 10, 6);	//10
	createLapMarkerTriggerVolume(11, 165.5f, 2, -85, 6, 10, 30);	//11
}
void PhysicsEngine::initAudioForVehicles(AudioEngine* audio) {
	this->audioEngine = audio;
	player->initVehicleAudio(this->audioEngine);
	for (int i = 0; i < enemyVehicles.size(); i++) {
		enemyVehicles[i]->initVehicleAudio(this->audioEngine);
	}
}

void PhysicsEngine::initAITrack(Track* raceTrack) {
	this->raceTrack = raceTrack;
}



void PhysicsEngine::addEnemyVehicle(float x, float y, float z)
{
	//create vehicle object
	//add it to the list of vehicle
	Vehicle* v = new Vehicle(false, gPhysics, gCooking, gMaterial, gScene, gAllocator, x, y, z, 2);
	v->initVehicleAudio(this->audioEngine);
	v->actor->userData = v;
	v->initAITrackPoints(&this->raceTrack->listOfPoints);
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
			Vehicle* fromList = enemyVehicles.at(i);
			if (fromList->isAICarStuck == true) {
				this->raceTrack->performStuckCorrectionMove(fromList);
			}
			else {
				this->raceTrack->performMove(fromList);
			}
			fromList->update(timestep, gScene);
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


/*
NOTE ABOUT THE TRIGGER VOLUMES:

The sizes are kind of wonky and hard to get right, PhysX doesn't let you see them so you have to experiment >:(
Just play around with the width, height and depth.
I find the smaller the box, the less duplicate collisions there are, but if your logic can handle duplicate
collisions that doesnt matter too much.


PLEASE PLEASE PLEASE USE THESE FUNCTIONS FOR ADDING TRIGGER VOLUMES! THIS WILL PREVENT LOTS OF PAIN AND SUFFERING!

*/


//creates a trigger volume at point (x,y,z) and adds it to the scene
//this is for pickups
void PhysicsEngine::createPickupTriggerVolume(float x, float y, float z, float width, float height, float depth)
{
	PickupBox* pickup = new PickupBox();

	PxBoxGeometry geometry(PxVec3(width / 2, height / 2, depth / 2));
	PxTransform transform(PxVec3(x, y, z), PxQuat(PxIDENTITY()));
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
	pickup->actor = actor;
	actor->setName(PICKUP.c_str());
	PxShape* shape;
	actor->getShapes(&shape, 1);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	pickup->actor->userData = pickup;

	gScene->addActor(*actor);
	pickupBoxes.push_back(pickup);
}

void PhysicsEngine::createLapMarkerTriggerVolume(int lapMarkerValue, float x, float y, float z, float width, float height, float depth)
{
	LapMarker* lapMarker = new LapMarker(lapMarkerValue);


	PxBoxGeometry geometry(PxVec3(width / 2, height / 2, depth / 2));
	PxTransform transform(PxVec3(x, y, z), PxQuat(PxIDENTITY()));
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
	lapMarker->actor = actor;
	actor->setName(LAPMARKER.c_str());
	PxShape* shape;
	actor->getShapes(&shape, 1);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	lapMarker->actor->userData = lapMarker;

	gScene->addActor(*actor);

	lapmarkers.push_back(lapMarker);
}

void PhysicsEngine::createCaltropsTriggerVolume(float x, float y, float z, float width, float height, float depth)
{
	//this creates a caltrop according to vehicle ability point logic at vehicle position and
	//adds it to the end of the list that gets passed in
	player->useCaltrops(&caltropsList);

	if(caltropsList.back() == NULL) {
		std::cout << "\nError: Could not create caltrops! No more charges!\n";
	}
	else {
		PxBoxGeometry geometry(PxVec3(width / 2, height / 2, depth / 2));
		PxTransform transform(PxVec3(x, y, z), PxQuat(PxIDENTITY()));
		PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

		PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
		caltropsList.back()->actor = actor;
		actor->setName(CALTROPS.c_str());
		PxShape* shape;
		actor->getShapes(&shape, 1);
		shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
		shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

		caltropsList.back()->actor->userData = caltropsList.back();

		gScene->addActor(*actor);
	}
}

void PhysicsEngine::createSmokeTriggerVolume(float x, float y, float z, float width, float height, float depth)
{
	//this creates a caltrop according to vehicle ability point logic at vehicle position and
	//adds it to the end of the list that gets passed in
	player->useSmoke(&smokeList);

	if (smokeList.back() == NULL) {
		std::cout << "\nError: Could not create smoke! No more charges!\n";
	}
	else {
		PxBoxGeometry geometry(PxVec3(width / 2, height / 2, depth / 2));
		PxTransform transform(PxVec3(x, y, z), PxQuat(PxIDENTITY()));
		PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

		PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
		smokeList.back()->actor = actor;
		actor->setName(SMOKE.c_str());
		PxShape* shape;
		actor->getShapes(&shape, 1);
		shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
		shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

		
		smokeList.back()->actor->userData = smokeList.back();

		gScene->addActor(*actor);
	}
}

void PhysicsEngine::createOilTriggerVolume(float x, float y, float z, float width, float height, float depth)
{
	//this creates a caltrop according to vehicle ability point logic at vehicle position and
	//adds it to the end of the list that gets passed in
	player->useOil(&oilList);

	if (oilList.back() == NULL) {
		std::cout << "\nError: Could not create oil! No more charges!\n";
	}
	else {
		PxBoxGeometry geometry(PxVec3(width / 2, height / 2, depth / 2));
		PxTransform transform(PxVec3(x, y, z), PxQuat(PxIDENTITY()));
		PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

		PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
		oilList.back()->actor = actor;
		actor->setName(OIL.c_str());
		PxShape* shape;
		actor->getShapes(&shape, 1);
		shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
		shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

		oilList.back()->actor->userData = oilList.back();

		gScene->addActor(*actor);
	}
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
}

