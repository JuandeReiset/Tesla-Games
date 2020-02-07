#include "PhysicsEngine.h"
#include "PhysX/PxPhysicsAPI.h"


using namespace physx;


//main physics class. Acts as the buffer between the game and PhysX
/*
	Should hold a list of all physics objects and updates them accordingly

	Individual objects with physics should have the physx type applied to them and managed through here

	Think of this as the main() for physics

	Should also hold the PVD code for visualization
*/
