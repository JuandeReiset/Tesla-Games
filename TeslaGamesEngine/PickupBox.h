#pragma once
#include "PhysicsObject.h"
/*
A trigger volume that holds the logic for our pickup boxes
*/
class PickupBox : public PhysicsObject
{
public:
	PickupBox();

	//true if the box has already been picked up, false otherwise
	bool getIsPicked() { return isPicked; }
	void setIsPicked();

private:
	bool isPicked;
};

