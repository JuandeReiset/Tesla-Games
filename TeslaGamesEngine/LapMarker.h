#pragma once
#include "PhysicsObject.h"
/*
An invisible trigger volume that holds the logic for counting laps during the race
*/
class LapMarker :
	public PhysicsObject
{
public:
	LapMarker(int value, physx::PxVec3 p);
	int markerValue;
	physx::PxVec3 markerPosition;
};

