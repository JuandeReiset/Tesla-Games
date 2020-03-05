#include "ColliderCallback.h"
#include <iostream>

using namespace std;

void ColliderCallback::onContact(const PxContactPairHeader & pairHeader, const PxContactPair * pairs, PxU32 nbPairs)
{
}

void ColliderCallback::onTrigger(PxTriggerPair * pairs, PxU32 count)
{
	cout << "\nGOT TO ONTRIGGER BODY\n";
	for (PxU32 i = 0; i < count; i++)
	{
		// ignore pairs when shapes have been deleted
		if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;

		//vehicle, collider
		if (1)//(pairs[i].otherActor == mSubmarineActor) && (pairs[i].triggerActor == gTreasureActor))
		{
			//logic on the trigger
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
			cout << "\nGOT TO ON TRIGGER LOGIC BLOCK\n";
		}
	}
}

void ColliderCallback::onSleep(PxActor ** actors, PxU32 count)
{
}

void ColliderCallback::onWake(PxActor ** actors, PxU32 count)
{
}

void ColliderCallback::onConstraintBreak(PxConstraintInfo * constraints, PxU32 count)
{
}

void ColliderCallback::onAdvance(const PxRigidBody * const * bodyBuffer, const PxTransform * poseBuffer, const PxU32 count)
{
}
