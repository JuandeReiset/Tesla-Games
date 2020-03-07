#include "ColliderCallback.h"
#include "Vehicle.h"
#include "LapMarker.h"
#include "PickupBox.h"
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

*/
void ColliderCallback::onTrigger(PxTriggerPair * pairs, PxU32 count)
{

	//NOTE: The otherActor and triggerActor are the vehicle(otherActor) and object(triggerActor) that collided


	for (PxU32 i = 0; i < count; i++)
	{
		// ignore pairs when shapes have been deleted
		if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;

		//vehicle and pickup box 
		if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "pickup") == 0)
		{
			cout << "\nTrigger Block: Pickup Box\n";

			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;	//this holds a ptr to the actual Vehicle object
			PickupBox* p = (PickupBox*)pairs[i].triggerActor->userData;	//this holds a ptr to the actual PickupBox object

			p->setIsPicked();
			//add logic here
		}
		//vehicle and lap marker/counter
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "lapmarker") == 0) {
			//cout << "\nTrigger Block: Lap Marker\n";

			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;
			LapMarker* l = (LapMarker*)pairs[i].triggerActor->userData;

			std::cout << "LAP MARKER VALUE: " << l->markerValue << std::endl;

			//hardcoded number of laps and markers
			v->hitLapMarker(l->markerValue, 3, 4);
			
		}
		//wont do yet, unsure how we want to handle the traps classes
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
