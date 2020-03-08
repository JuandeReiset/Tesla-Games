#pragma once
#include "PhysicsObject.h"
/*
A trigger volume that holds the logic for our pickup boxes
*/
class PickupBox : public PhysicsObject
{
public:
	PickupBox();

	bool getIsPicked() { return isPicked; }
	void setIsPicked();

private:
	bool isPicked;
};

