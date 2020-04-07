#include "ColliderCallback.h"
#include "Vehicle.h"
#include "LapMarker.h"
#include "PickupBox.h"
#include "AmmoBox.h"
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
			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;	//this holds a ptr to the actual Vehicle object
			PickupBox* p = (PickupBox*)pairs[i].triggerActor->userData;	//this holds a ptr to the actual PickupBox object


			//if the box hasnt been picked up yet
			//if you are ranked 1 the pickup is disabled, or if you have max charges
			if (!p->getIsPicked() /*&& v->ranking != 1 && v->ability != 9*/) {	//this avoids hitting the same box multiple times
				//cout << "\nTrigger Block: Pickup Box\n";
				p->setIsPicked();
				v->pickup();
			}
		}
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "ammo") == 0) {
			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;	//this holds a ptr to the actual Vehicle object
			AmmoBox* a = (AmmoBox*)pairs[i].triggerActor->userData;	//this holds a ptr to the actual PickupBox object

			//if the box hasnt been picked up yet
			if (!a->getIsPicked() /*&& v->ranking != 1 && v->getShootingComponent()->ammo != 10*/) {	//this avoids hitting the same box multiple times
				//cout << "\nTrigger Block: Ammo Box\n";
				a->setIsPicked();
				v->ammo();
			}

		}
		//vehicle and lap marker/counter
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "lapmarker") == 0) {
			//cout << "\nTrigger Block: Lap Marker\n";

			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;
			LapMarker* l = (LapMarker*)pairs[i].triggerActor->userData;

			 std::cout << "LAP MARKER VALUE: " << l->markerValue << std::endl;

			//hardcoded number of laps and markers
			v->hitLapMarker(l->markerValue, 1);	//5 laps
			
		}
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "caltrops") == 0) {
			//cout << "\nTrigger Block: Caltrops\n";

			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;
			Caltrops* c = (Caltrops*)pairs[i].triggerActor->userData;

			//cout << "CALTROPS ID: " << c->id << " VEHICLE: "<<v->ID<<"\n";

			//should do damage (1pt) and should not hit the player it was placed by
			if (v->ID != c->id) {

				if (!(!v->isPlayer && c->id == -69420)) {
					
					//cout << "DAMAGE DEALT\n";
					//do damage
					v->takeCaltropDamage(c->id, 1);
				} 
				//else
					//cout << "AI TRACK TRAP COLLISION\n";
				
			}
		}
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "smoke") == 0) {
			//cout << "\nTrigger Block: Smoke\n";

			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;
			Smoke* s = (Smoke*)pairs[i].triggerActor->userData;

			//cout << "SMOKE ID: " << s->id << " VEHICLE: " << v->ID << "\n";

			//should do damage (1pt) and should not hit the player it was placed by
			if (v->ID != s->id) {
				//smoke gameplay effect
				if(!v->affectedBySmoke && !(!v->isPlayer && s->id == -69420))
					v->enableSmokeEffect();
				//else
					//cout << "AI TRACK TRAP COLLISION\n";
			}
		}
		else if (strcmp(pairs[i].otherActor->getName(), "vehicle") == 0 && strcmp(pairs[i].triggerActor->getName(), "oil") == 0) {
			//cout << "\nTrigger Block: Oil\n";

			Vehicle* v = (Vehicle*)pairs[i].otherActor->userData;
			Oil* o = (Oil*)pairs[i].triggerActor->userData;

			//cout << "OIL ID: " << o->id << " VEHICLE: " << v->ID << "\n";
			//should do damage (1pt) and should not hit the player it was placed by
			if (v->ID != o->id) {
				//oil gameplay effect
				if(!v->affectedByOil && !(!v->isPlayer && o->id == -69420))
					v->enableOilEffect();
				//else
					//cout << "AI TRACK TRAP COLLISION\n";
			}
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
