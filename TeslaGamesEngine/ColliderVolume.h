#pragma once
#include "../include/PhysX/PxPhysicsAPI.h"



using namespace physx;
//Represents hitboxes or zones
//Can be used for collision boxes for pickups, collisions for traps, lap markers, etc
class ColliderVolume
{
	//flags, constructor
	//doesnt need to be added to scene or have an update function
public:
	PxRigidActor* triggerActor;


	float x, y, z;

	ColliderVolume(PxPhysics* gPhysics, float x, float y, float z);
};

