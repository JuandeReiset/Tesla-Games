#include "ColliderCallback.h"
#include "Vehicle.h"
#include "LapMarker.h"
#include <iostream>

using namespace std;

void ColliderCallback::onContact(const PxContactPairHeader & pairHeader, const PxContactPair * pairs, PxU32 nbPairs)
{
}

/*
WARNING WARNING WARNING WARNING

Due to how PhysX is coded, onTrigger will be called as long as the 2 objects are overlapping and moving! This means a vehicle moving
through a trigger volume will call it MULTIPLE TIMES (once per frame if they overlap)! Please code logic in here to check if you have 
already done the check for your event!

FUN FACT: The smaller the trigger volume is, the less times it will trigger! 

*/
void ColliderCallback::onTrigger(PxTriggerPair * pairs, PxU32 count)
{
	for (PxU32 i = 0; i < count; i++)
	{
		// ignore pairs when shapes have been deleted
		if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;

		//vehicle and pickup box 
		if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "pickup") == 0)
		{
			cout << "\nTrigger Block: Pickup Box\n";	//Fun Note: Driving through this triggers it about 15 times (once per frame)!

			//add logic here
		}
		//vehicle and lap marker/counter
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "lapmarker") == 0) {
			cout << "\nTrigger Block: Lap Marker\n";

			Vehicle* v = (Vehicle*)pairs[i].otherActor;
			LapMarker* l = (LapMarker*)pairs[i].triggerActor;

			//hardcoded number of laps and markers
			v->hitLapMarker(l->markerValue, 3, 4);
			
		}
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "hazard") == 0) {
			cout << "\nTrigger Block: Hazard\n";

			//add logic here
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
