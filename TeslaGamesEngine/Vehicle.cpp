#include "Vehicle.h"
#include <iostream>
#include <ctype.h>


using namespace physx;
using namespace snippetvehicle;

Vehicle::Vehicle(PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, PxDefaultAllocator gAllocator, float x, float y, float z) {
	physx::PxF32 gSteerVsForwardSpeedData[] =
	{
		0.0f,		0.75f,
		5.0f,		0.75f,
		30.0f,		0.125f,
		120.0f,		0.1f,
		PX_MAX_F32, PX_MAX_F32,
		PX_MAX_F32, PX_MAX_F32,
		PX_MAX_F32, PX_MAX_F32,
		PX_MAX_F32, PX_MAX_F32
	};

	Vehicle::gSteerVsForwardSpeedTable = PxFixedSizeLookupTable<8>(gSteerVsForwardSpeedData, 4);

	Vehicle::gKeySmoothingData =
	{
		{
			6.0f,	//rise rate eANALOG_INPUT_ACCEL
			6.0f,	//rise rate eANALOG_INPUT_BRAKE		
			6.0f,	//rise rate eANALOG_INPUT_HANDBRAKE	
			2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT
			2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT
		},
		{
			10.0f,	//fall rate eANALOG_INPUT_ACCEL
			10.0f,	//fall rate eANALOG_INPUT_BRAKE		
			10.0f,	//fall rate eANALOG_INPUT_HANDBRAKE	
			5.0f,	//fall rate eANALOG_INPUT_STEER_LEFT
			5.0f	//fall rate eANALOG_INPUT_STEER_RIGHT
		}
	};

	gPadSmoothingData =
	{
		{
			6.0f,	//rise rate eANALOG_INPUT_ACCEL
			6.0f,	//rise rate eANALOG_INPUT_BRAKE		
			6.0f,	//rise rate eANALOG_INPUT_HANDBRAKE	
			2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT
			2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT
		},
		{
			10.0f,	//fall rate eANALOG_INPUT_ACCEL
			10.0f,	//fall rate eANALOG_INPUT_BRAKE		
			10.0f,	//fall rate eANALOG_INPUT_HANDBRAKE	
			5.0f,	//fall rate eANALOG_INPUT_STEER_LEFT
			5.0f	//fall rate eANALOG_INPUT_STEER_RIGHT
		}
	};

	initVehicle(gPhysics, gCooking, gMaterial, gScene, gAllocator, PxVec3(x, y, z));
}
Vehicle::Vehicle(int id) : ID(id) {}
Vehicle::~Vehicle() {}

//takes in timestep, updates all vehicle physics. Called by PhysicsEngine
void Vehicle::update(PxF32 timestep, PxScene* gScene)
{
	PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs(gPadSmoothingData, gSteerVsForwardSpeedTable, gVehicleInputData, timestep, gIsVehicleInAir, *gVehicle4W);

	//Raycasts.
	PxVehicleWheels* vehicles[1] = { gVehicle4W };
	PxRaycastQueryResult* raycastResults = gVehicleSceneQueryData->getRaycastQueryResultBuffer(0);
	const PxU32 raycastResultsSize = gVehicleSceneQueryData->getQueryResultBufferSize();
	PxVehicleSuspensionRaycasts(gBatchQuery, 1, vehicles, raycastResultsSize, raycastResults);

	//Vehicle update.
	const PxVec3 grav = gScene->getGravity();
	PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
	PxVehicleWheelQueryResult vehicleQueryResults[1] = { {wheelQueryResults, gVehicle4W->mWheelsSimData.getNbWheels()} };
	PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	//Work out if the vehicle is in the air.
	gIsVehicleInAir = gVehicle4W->getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);
}

//called by PhysicsEngine. Parameters are disgusting I know, but sometimes it must be ugly to work
void Vehicle::initVehicle(PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, PxDefaultAllocator gAllocator, PxVec3 position)
{
	PxInitVehicleSDK(*gPhysics);
	PxVehicleSetBasisVectors(PxVec3(0, 1, 0), PxVec3(0, 0, 1));
	PxVehicleSetUpdateMode(PxVehicleUpdateMode::eVELOCITY_CHANGE);

	//Create the batched scene queries for the suspension raycasts.
	Vehicle::gVehicleSceneQueryData = VehicleSceneQueryData::allocate(1, PX_MAX_NB_WHEELS, 1, 1, WheelSceneQueryPreFilterBlocking, NULL, gAllocator);
	gBatchQuery = VehicleSceneQueryData::setUpBatchedSceneQuery(0, *gVehicleSceneQueryData, gScene);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);

	//Create a vehicle that will drive on the plane.
	VehicleDesc vehicleDesc = initVehicleDesc(gMaterial);
	gVehicle4W = createVehicle4W(vehicleDesc, gPhysics, gCooking);
	PxTransform startTransform(PxVec3(0, (vehicleDesc.chassisDims.y * 0.5f + vehicleDesc.wheelRadius + 1.0f), 0), PxQuat(PxIdentity));
	startTransform.p = position;	//dear lord I hope this works
	actor = gVehicle4W->getRigidDynamicActor();	//set vehicle dynamic to the PhysxObject actor
	gVehicle4W->getRigidDynamicActor()->setGlobalPose(startTransform);
	gScene->addActor(*gVehicle4W->getRigidDynamicActor());

	//Set the vehicle to rest in first gear.
	//Set the vehicle to use auto-gears.
	gVehicle4W->setToRestState();
	gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	gVehicle4W->mDriveDynData.setUseAutoGears(true);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VehicleDesc Vehicle::initVehicleDesc(PxMaterial* gMaterial)	//pass in gMaterial from PhysicsEngine
{
	//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
	//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
	//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.
	const PxF32 chassisMass = 1500.0f;
	const PxVec3 chassisDims(2.5f, 2.0f, 5.0f);
	const PxVec3 chassisMOI
	((chassisDims.y * chassisDims.y + chassisDims.z * chassisDims.z) * chassisMass / 12.0f,
		(chassisDims.x * chassisDims.x + chassisDims.z * chassisDims.z) * 0.8f * chassisMass / 12.0f,
		(chassisDims.x * chassisDims.x + chassisDims.y * chassisDims.y) * chassisMass / 12.0f);
	const PxVec3 chassisCMOffset(0.0f, -chassisDims.y * 0.5f + 0.65f, 0.25f);

	//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
	//Moment of inertia is just the moment of inertia of a cylinder.
	const PxF32 wheelMass = 20.0f;
	const PxF32 wheelRadius = 0.5f;
	const PxF32 wheelWidth = 0.4f;
	const PxF32 wheelMOI = 0.5f * wheelMass * wheelRadius * wheelRadius;
	const PxU32 nbWheels = 6;

	VehicleDesc vehicleDesc;


	vehicleDesc.chassisMass = chassisMass;
	vehicleDesc.chassisDims = chassisDims;
	vehicleDesc.chassisMOI = chassisMOI;
	vehicleDesc.chassisCMOffset = chassisCMOffset;
	vehicleDesc.chassisMaterial = gMaterial;
	vehicleDesc.chassisSimFilterData = PxFilterData(COLLISION_FLAG_CHASSIS, COLLISION_FLAG_CHASSIS_AGAINST, 0, 0);

	vehicleDesc.wheelMass = wheelMass;
	vehicleDesc.wheelRadius = wheelRadius;
	vehicleDesc.wheelWidth = wheelWidth;
	vehicleDesc.wheelMOI = wheelMOI;
	vehicleDesc.numWheels = nbWheels;
	vehicleDesc.wheelMaterial = gMaterial;
	vehicleDesc.chassisSimFilterData = PxFilterData(COLLISION_FLAG_WHEEL, COLLISION_FLAG_WHEEL_AGAINST, 0, 0);

	return vehicleDesc;
}

//cleans the physx objects. Gets called in PhysicsEngine
void Vehicle::cleanupPhysics(PxDefaultAllocator gAllocator) {
	gVehicle4W->getRigidDynamicActor()->release();
	gVehicle4W->free();

	PX_RELEASE(gBatchQuery);
	gVehicleSceneQueryData->free(gAllocator);
	PX_RELEASE(gFrictionPairs);
	PxCloseVehicleSDK();
}

void Vehicle::startAccelerateForwardsMode(float magnitude)
{
	gVehicleInputData.setAnalogAccel(1.0f);

}

void Vehicle::startAccelerateReverseMode(float magnitude)
{
	gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);

	gVehicleInputData.setAnalogAccel(1.0f);
}

void Vehicle::startBrakeMode()
{
	gVehicleInputData.setAnalogBrake(1.0f);
}

void Vehicle::startTurnHardLeftMode(float magnitude)
{
	magnitude = abs(magnitude);
	gVehicleInputData.setAnalogAccel(true);
	gVehicleInputData.setAnalogSteer(-magnitude);

}

void Vehicle::startTurnHardRightMode(float magnitude)
{
	magnitude = abs(magnitude);
	gVehicleInputData.setAnalogAccel(magnitude);
	gVehicleInputData.setAnalogSteer(magnitude);

}

void Vehicle::startHandbrakeTurnLeftMode(float magnitude)
{
	magnitude = abs(magnitude);
	gVehicleInputData.setAnalogSteer(-magnitude);
	gVehicleInputData.setAnalogHandbrake(magnitude);

}

void Vehicle::startHandbrakeTurnRightMode(float magnitude)
{
	magnitude = abs(magnitude);
	gVehicleInputData.setAnalogSteer(magnitude);
	gVehicleInputData.setAnalogHandbrake(magnitude);
}

void Vehicle::releaseAllControls()
{
	if (gMimicKeyInputs)
	{
		gVehicleInputData.setDigitalAccel(false);
		gVehicleInputData.setDigitalSteerLeft(false);
		gVehicleInputData.setDigitalSteerRight(false);
		gVehicleInputData.setDigitalBrake(false);
		gVehicleInputData.setDigitalHandbrake(false);
	}
	else
	{
		gVehicleInputData.setAnalogAccel(0.0f);
		gVehicleInputData.setAnalogSteer(0.0f);
		gVehicleInputData.setAnalogBrake(0.0f);
		gVehicleInputData.setAnalogHandbrake(0.0f);
	}
}

//go forwards a little
void Vehicle::forwards(float magnitude)
{
	gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	gVehicleInputData.setAnalogAccel(magnitude - 0.3f);
}

void Vehicle::reverse(float magnitude)
{
	gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
	gVehicleInputData.setAnalogAccel(magnitude);
}

void Vehicle::turn(float magnitude) {
	gVehicleInputData.setAnalogSteer(-magnitude);

}

void Vehicle::turnLeft(float magnitude)
{
	gVehicleInputData.setAnalogSteer(-1.0f);
}

void Vehicle::turnRight(float magnitude)
{
	gVehicleInputData.setAnalogSteer(1.0f);
}

void Vehicle::brake()
{
	gVehicleInputData.setAnalogBrake(0.5f);
}

//returns the position of the physx vehicle model as a PxVec3. You can easily convert this to a glm vec3
PxVec3 Vehicle::GetPosition()
{
	PxVec3 position = gVehicle4W->getRigidDynamicActor()->getGlobalPose().p;
	return position;
}

float Vehicle::GetRotationAngle()
{
	return gVehicle4W->getRigidDynamicActor()->getGlobalPose().q.getAngle();
}

void Vehicle::keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	PX_UNUSED(key);
}

void Vehicle::Tick(float deltaTime) {
	std::cout << "Current health:" << currentHealth() << std::endl;
	if (currentHealth() <= 0)
		dead_flag = 1;

	if (ID == combat.GetTargetID())
		getDamage(combat.GetDamage());

	if (turret.get_ammo_counter()<=0)
		armed = false;
		
}

double Vehicle::currentHealth() {
	return health.GetHealth();
}

void Vehicle::getDamage(double damage) {
	double h = health.GetHealth();
	health.SetHealth(h - damage);

	return;
}

void Vehicle::firelazer() {
	turret.fire();
}

