#include "ColliderVolume.h"
#include <iostream>

using namespace physx;

ColliderVolume::ColliderVolume(PxPhysics* gPhysics, float x, float y, float z)
{
	//define triggerActor
	triggerActor = gPhysics->createRigidStatic(PxTransform(PxVec3(x, y, z)));

	PxShape* testShape;
	/*
	to define size:
	physeng




	*/

	//testShape->setGeometry(PxBoxGeometry(PxVec3(2, 2, 2)));
	triggerActor->getShapes(&testShape, 1);
	testShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	testShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

}
