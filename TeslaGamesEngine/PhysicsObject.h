#pragma once
#include "Object.h"
#include "../include/PhysX/PxPhysicsAPI.h"
class PhysicsObject :
	public Object
{
public:
	physx::PxRigidActor* actor;

	void Tick(float deltaTime);
};

