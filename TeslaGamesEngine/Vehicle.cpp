#include "Vehicle.h"
#include <iostream>
#include <ctype.h>


using namespace physx;
using namespace snippetvehicle;

Vehicle::Vehicle(PxPhysics* gPhysics, PxCooking* gCooking, PxMaterial* gMaterial, PxScene* gScene, PxDefaultAllocator gAllocator, float x, float y, float z, int id, std::vector<LapMarker*>* markers) {
	physx::PxF32 gSteerVsForwardSpeedData[] =
	{
		0.0f,		0.9f,
		5.0f,		0.75f,
		15.0f,		0.55f,
		30.0f,		0.35f,
		120.0f,		0.15f,
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

	ID = id;

	ability = 3;	//each vehicle has 3 ability use by default

	numberOfMarkersInTrack = markers->size();
	totalMarkersHit = 0;
	lapMarkers = markers;

	hasWon = false;
	winRank = 0;
}
Vehicle::Vehicle(int id) : ID(id) {}
Vehicle::~Vehicle() { cleanup(); }

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

	audioUpdate();
	float curSpeed = gVehicle4W->computeForwardSpeed();
	float curAccel = gVehicleInputData.getAnalogAccel();
	

	speedFrameIndex++;
	if (speedFrameIndex % 15 == 0) {
		speedFrameIndex = 0;
		previousSpeed = curSpeed;
		previousAccel = curAccel;
	}

	update_turret();


	//run smoke and oil effects 
	updateCurrentTime();
	updateSmoke();
	updateOil();

	//update distance for position/ranking
	updateDistance();
	
	//Update the list of caltrops that can hurt the racer
	updateCaltropEffectList();

	if (this->isAICar) {
		PxVec3 pos = this->GetPosition();
		PxVec3 target = PxVec3(this->curTarget.x, this->curTarget.y, this->curTarget.z);
		PxVec3 toTargetVec = (target - pos);
		float distanceToTarget = toTargetVec.magnitude();

		if (distanceToTarget <= this->curTarget.pointDistanceLimit) {
			this->incrementAITrackPoint();
			bool isAICarStuck = false;
		}
		else {
			//Check for getting stuck
			this->AICarStuckFrameCounter = (AICarStuckFrameCounter + 1) % 480;
			if (this->AICarStuckFrameCounter == 0 || this->isAICarStuck == true) {
				if (this->oldStuckTarget.actionToTake == -1) {
					this->oldStuckTarget = this->curTarget;
				}
				else {
					if (this->oldStuckTarget == this->curTarget) {
						if (this->isAICarStuck == false) {
							float speed = std::abs(this->gVehicle4W->computeForwardSpeed());
							if (speed < 3.f) {
								this->isAICarStuck = true;
							}
						}
						else {
							this->AICarStuckMoveCounter = (this->AICarStuckMoveCounter + 1) % 120;
							if (this->AICarStuckMoveCounter == 0) {
								this->isAICarStuck = false;
							}
						}
					}
					else {
						this->oldStuckTarget = this->curTarget;
					}
				}
			}
		}
	}
}

//updates the distance from this vehicle to the next lap marker
void Vehicle::updateDistance()
{
	PxVec3 vehiclePos(actor->getGlobalPose().p);
	PxVec3 markerPos(lapMarkers->at(expectedMarker)->actor->getGlobalPose().p);

	distance = sqrt(pow((markerPos.x - vehiclePos.x), 2) + pow((markerPos.y - vehiclePos.y), 2) + pow((markerPos.z - vehiclePos.z), 2));
}

//called when a vehicle hits a trigger volume lap marker. Val is the lapMarker value, trackTotalLaps is the
//total number of laps needed to win on that track, trackTotalLapMarkers is the total number of lap markers
//placed around the track
void Vehicle::hitLapMarker(int val, int trackTotalLaps)
{
	if (expectedMarker == val) {	//good hit
		//std::cout << "HIT LAP MARKER " << val << "!\n";
		totalMarkersHit++;
		//update expected and current marker vals
		expectedMarker = (expectedMarker + 1) % numberOfMarkersInTrack;
		currentMarker = (currentMarker + 1) % numberOfMarkersInTrack;

		//start marker is 0, first marker after start is 1
		if (currentMarker == 0 && expectedMarker == 1) {	//completed a lap
			numLaps++;
			if (numLaps == trackTotalLaps && ranking == 1) {	//you win!
				wins();
			}
		}
	}
}


void Vehicle::wins()
{
	hasWon = true;
	winRank = ranking;
}


void Vehicle::initAITrackPoints(std::vector<std::unique_ptr<TrackDrivingPoint>>* listOfPoints) {
	this->listOfPoints = listOfPoints;
	this->pastTarget = *this->listOfPoints->at(0);
	this->curTarget = *this->listOfPoints->at(1);
	this->isAICar = true;
	this->trackPointListIndex = 1;
}

void Vehicle::incrementAITrackPoint() {
	int length = this->listOfPoints->size();
	this->pastTarget = curTarget;
	this->trackPointListIndex++;
	this->trackPointListIndex = this->trackPointListIndex % length;
	this->curTarget = *this->listOfPoints->at(trackPointListIndex);
}


void Vehicle::update_turret() {
	PxVec3 pxpos = GetPosition();
	glm::vec3 pos;

	PxQuat vehicleQuaternion = gVehicle4W->getRigidDynamicActor()->getGlobalPose().q;
	PxVec3 v_dir = vehicleQuaternion.getBasisVector2();

	pos.x = pxpos.x;
	pos.x = pxpos.y;
	pos.z = pxpos.z;
	turret.updatePosition(pos);
	turret.updateDirection(v_dir.x,v_dir.y,v_dir.z);
}

void Vehicle::shoot(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float x, float y, float z) {
	PxQuat vehicleQuaternion = gVehicle4W->getRigidDynamicActor()->getGlobalPose().q;
	PxVec3 v_dir = vehicleQuaternion.getBasisVector2();
	PxVec3 pxpos = GetPosition();
	glm::vec3 pos;
	pos.x = pxpos.x;
	pos.x = pxpos.y;
	pos.z = pxpos.z;
	turret.fire(pos, uniModel, uniSpecularIntensity, uniShininess, v_dir.x, v_dir.y, v_dir.z);
	//turret.createBullet(pos,  uniModel, uniSpecularIntensity,  uniShininess, v_dir.x, v_dir.y, v_dir.z);
    
}

void Vehicle::renderBullets() {
	turret.renderAllBullets();
}

ShootComp* Vehicle::getShootingComponent() {
	return &turret;
}

void Vehicle::update_health() {
	int currentHealth = health.GetHealth();
	health.SetHealth(currentHealth-10);
}

HealthComponent* Vehicle::getHealthComponent() {
	return &health;
}

void Vehicle::cleanup() {
	this->audioEngine->killSource(&this->accelerateFromRest);
	this->audioEngine->killSource(&this->accelerateFromMotion);
	this->audioEngine->killSource(&this->boostStart);
	this->audioEngine->killSource(&this->boostMax);
	this->audioEngine->killSource(&this->maxSpeed);

	this->audioEngine->killSource(&this->deployCaltropsEffect);
	this->audioEngine->killSource(&this->deployOilEffect);
	this->audioEngine->killSource(&this->deploySmokeEffect);
}

void Vehicle::audioUpdate() {
	PxVec3 position = GetPosition();

	this->accelerateFromRest.updateSourcePosition(position.x, position.y, position.z);
	this->accelerateFromMotion.updateSourcePosition(position.x, position.y, position.z);
	this->boostStart.updateSourcePosition(position.x, position.y, position.z);
	this->boostMax.updateSourcePosition(position.x, position.y, position.z);
	this->maxSpeed.updateSourcePosition(position.x, position.y, position.z);

	this->deployCaltropsEffect.updateSourcePosition(position.x, position.y, position.z);
	this->deployOilEffect.updateSourcePosition(position.x, position.y, position.z);
	this->deploySmokeEffect.updateSourcePosition(position.x, position.y, position.z);

	this->turret.updateAudioPosition(position.x, position.y, position.z);
	this->health.setPosition(position.x, position.y, position.z);
}



void Vehicle::handleSound() {
	float curSpeed = std::abs(gVehicle4W->computeForwardSpeed());
	float slideSpeed = std::abs(gVehicle4W->computeSidewaysSpeed());
	PxU32 curGear = gVehicle4W->mDriveDynData.getCurrentGear();
	float curAccel = gVehicleInputData.getAnalogAccel();
	float curBrake = gVehicleInputData.getAnalogBrake();

	float speedSoundBoundary = 0.3f;
	float slideSpeedBoundary = 1.3f;
	if (curSpeed <= speedSoundBoundary && slideSpeed <= slideSpeedBoundary) {
		this->accelerateFromRest.stopSound();
		this->accelerateFromMotion.stopSound();
		this->boostStart.stopSound();
		this->boostMax.stopSound();
		this->maxSpeed.stopSound();
	}
	else if (curSpeed <= speedSoundBoundary && slideSpeed > slideSpeedBoundary) {
		this->accelerateFromRest.stopSound();
		this->accelerateFromMotion.stopSound();
		this->boostStart.stopSound();
		this->boostMax.stopSound();
		if (!this->maxSpeed.isSoundPlaying()) {
			this->maxSpeed.playSound();
		}
	}
	else {
		if (curBrake > 0.f) {
			this->accelerateFromRest.stopSound();
			this->accelerateFromMotion.stopSound();
			this->boostMax.stopSound();
			if (curSpeed > speedSoundBoundary) {
				if (!this->maxSpeed.isSoundPlaying()) {
					this->maxSpeed.playSound();
				}
			}
			else {
				this->maxSpeed.stopSound();
			}
		}
		else {
			if (curAccel > 0.1f) {
				if (curAccel > previousAccel) {
					if (curGear == PxVehicleGearsData::eFIRST) {
						this->maxSpeed.stopSound();
						this->accelerateFromMotion.stopSound();
						this->boostMax.stopSound();
						if (!this->accelerateFromRest.isSoundPlaying()) {
							this->accelerateFromRest.playSound();
						}
					}
					else if (curGear == PxVehicleGearsData::eREVERSE) {
						this->accelerateFromMotion.stopSound();
						this->boostMax.stopSound();
						this->accelerateFromRest.stopSound();
						if (!this->maxSpeed.isSoundPlaying()) {
							this->maxSpeed.playSound();
						}
					}
					else {
						this->maxSpeed.stopSound();
						this->boostMax.stopSound();
						this->accelerateFromRest.stopSound();
						if (!this->accelerateFromMotion.isSoundPlaying()) {
							this->accelerateFromMotion.playSound();
						}
					}
				}
				else {
					if (curGear == PxVehicleGearsData::eFIRST) {
						this->maxSpeed.stopSound();
						this->boostMax.stopSound();
						this->accelerateFromMotion.stopSound();
						if (!this->accelerateFromRest.isSoundPlaying()) {
							this->accelerateFromRest.playSound();
						}
					}
					else if (curGear == PxVehicleGearsData::eREVERSE) {
						this->accelerateFromMotion.stopSound();
						this->boostMax.stopSound();
						this->accelerateFromRest.stopSound();
						if (!this->maxSpeed.isSoundPlaying()) {
							this->maxSpeed.playSound();
						}
					}
					else if ((previousSpeed - 1.f) > curSpeed && slideSpeed <= slideSpeedBoundary) {
						this->maxSpeed.stopSound();
						this->boostMax.stopSound();
						this->accelerateFromRest.stopSound();
						if (!this->accelerateFromMotion.isSoundPlaying()) {
							this->accelerateFromMotion.playSound();
						}
					}
					else {
						if (!this->accelerateFromMotion.isSoundPlaying() && (!this->accelerateFromRest.isSoundPlaying())) {
							this->maxSpeed.stopSound();
							if (!this->boostMax.isSoundPlaying()) {
								this->boostMax.playSound();
							}
						}
					}
				}
				
			}
			else {
				this->accelerateFromRest.stopSound();
				this->accelerateFromMotion.stopSound();
				this->boostMax.stopSound();
				if (curSpeed > speedSoundBoundary) {
					if (!this->maxSpeed.isSoundPlaying()) {
						this->maxSpeed.playSound();
					}
				}
				else {
					this->maxSpeed.stopSound();
				}
			}
		}
	}
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
	PxTransform startTransform(PxVec3(0, (vehicleDesc.chassisDims.y * 0.5f + vehicleDesc.wheelRadius + 1.0f), 0), PxQuat(-1.5708f, PxVec3(0, 1, 0)));
	startTransform.p = position;	//dear lord I hope this works
	actor = gVehicle4W->getRigidDynamicActor();	//set vehicle dynamic to the PhysxObject actor
	actor->setName("vehicle");
	gVehicle4W->getRigidDynamicActor()->setGlobalPose(startTransform);
	gScene->addActor(*gVehicle4W->getRigidDynamicActor());

	//Set the vehicle to rest in first gear.
	//Set the vehicle to use auto-gears.
	gVehicle4W->setToRestState();
	gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eNEUTRAL);
	gVehicle4W->mDriveDynData.setUseAutoGears(true);

	//set default info for laps
	currentMarker = 0;
	expectedMarker = 1;
	numLaps = 0;
	ranking = 0;

	smokeDuration = 10.f;
	oilDuration = 5.f;

}

void Vehicle::initVehicleAudio(AudioEngine* engine) {
	this->audioEngine = engine;
	this->accelerateFromRest = audioEngine->createBoomBox(audioConstants::SOUND_FILE_ACCEL_REST);
	this->accelerateFromMotion = audioEngine->createBoomBox(audioConstants::SOUND_FILE_ACCEL_MOTION);
	this->boostStart = audioEngine->createBoomBox(audioConstants::SOUND_FILE_BOOST_START);
	this->boostMax = audioEngine->createBoomBox(audioConstants::SOUND_FILE_BOOST_MAX);
	this->maxSpeed = audioEngine->createBoomBox(audioConstants::SOUND_FILE_SPEED_MAX);

	this->deployCaltropsEffect = audioEngine->createBoomBox(audioConstants::SOUND_FILE_DEPLOY_CALTROPS);
	this->deployOilEffect = audioEngine->createBoomBox(audioConstants::SOUND_FILE_DEPLOY_OIL);
	this->deploySmokeEffect = audioEngine->createBoomBox(audioConstants::SOUND_FILE_DEPLOY_SMOKE);

	this->turret.initShootCompAudio(engine);
	this->health.initAudioForHealthComponent(engine);

	float initialSoundVolume = 15.f;

	this->accelerateFromRest.setVolume(initialSoundVolume);
	this->accelerateFromMotion.setVolume(initialSoundVolume);
	this->boostStart.setVolume(initialSoundVolume);
	this->boostMax.setVolume(initialSoundVolume);
	this->maxSpeed.setVolume(initialSoundVolume);
	this->deployCaltropsEffect.setVolume(initialSoundVolume);
	this->deployOilEffect.setVolume(initialSoundVolume);
	this->deploySmokeEffect.setVolume(initialSoundVolume);
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

//this should go with the vehicle class
void Vehicle::gearShift(float curSpeed) {
	PxU32 curGear = gVehicle4W->mDriveDynData.getCurrentGear();
	if (curSpeed <= 10) {
		if (curGear != PxVehicleGearsData::eFIRST) {
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
		}
	}
	else if (curSpeed <= 17) {
		if (curGear != PxVehicleGearsData::eSECOND) {
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eSECOND);
		}
	}
	else if (curSpeed <= 25) {
		if (curGear != PxVehicleGearsData::eTHIRD) {
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eTHIRD);
		}
	}
	else if (curSpeed <= 34) {
		if (curGear != PxVehicleGearsData::eFOURTH) {
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFOURTH);
		}
	}
	else {
		if (curGear != PxVehicleGearsData::eFIFTH) {
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIFTH);
		}
	}
}

void Vehicle::handbrakeTurn(float magnitudeBrake, float magnitudeTurn)
{
	gVehicleInputData.setAnalogSteer(magnitudeTurn);
	gVehicleInputData.setAnalogHandbrake(magnitudeBrake);

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
	float curSpeed = gVehicle4W->computeForwardSpeed();
	gearShift(curSpeed);
	gVehicleInputData.setAnalogBrake(0.f);
	gVehicleInputData.setAnalogAccel(magnitude);
	handleSound();
}

void Vehicle::reverse(float magnitude)
{
	float curSpeed = gVehicle4W->computeForwardSpeed();
	if (curSpeed > 0.f) {
		gearShift(curSpeed);
		gVehicleInputData.setAnalogBrake(magnitude);
	}
	else {
		gVehicleInputData.setAnalogBrake(0.f);
		if (gVehicle4W->mDriveDynData.getCurrentGear() != PxVehicleGearsData::eREVERSE) {
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
		}
		
		gVehicleInputData.setAnalogAccel(magnitude);
	}
	handleSound();
}

void Vehicle::turn(float magnitude) {
	gVehicleInputData.setAnalogSteer(-magnitude);
}


//returns the position of the physx vehicle model as a PxVec3. You can easily convert this to a glm vec3
PxVec3 Vehicle::GetPosition()
{
	PxVec3 position = gVehicle4W->getRigidDynamicActor()->getGlobalPose().p;
	return position;
}

physx::PxTransform Vehicle::GetTransform()
{
	return gVehicle4W->getRigidDynamicActor()->getGlobalPose();
}

float Vehicle::GetForwardsSpeed()
{
	return gVehicle4W->computeForwardSpeed();
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
void Vehicle::Tick(float deltaTime) {}

double Vehicle::currentHealth() {
	return health.GetHealth();
}

void Vehicle::takeTrapDamage(double dmgAmount) {
	this->health.takeTrapDamage(dmgAmount);
}

void Vehicle::takeCaltropDamage(int caltropId, double dmgAmount) {
	bool foundCaltropAlreadyInList = false;
	int caltropEffectTimeToLive = 45; //number is number of frames bewteen hits allowed

	for (int i = 0; i < this->caltropEffectPairList.size(); i = i + 2) {
		int id = this->caltropEffectPairList[i];
		if (caltropId == id) {
			foundCaltropAlreadyInList = true;
			break;
		}
	}
	if (foundCaltropAlreadyInList == false) {
		this->caltropEffectPairList.push_back(caltropId);
		this->caltropEffectPairList.push_back(caltropEffectTimeToLive);
		this->takeTrapDamage(dmgAmount);
	}
}

void Vehicle::updateCaltropEffectList() {

	std::vector<int> indiciesToRemove;

	for (int i = 0; i < this->caltropEffectPairList.size(); i = i + 2) {
		int indexOfCaltrop = this->caltropEffectPairList[i];
		int framesToLive = this->caltropEffectPairList[i + 1];
		framesToLive--;
		if (framesToLive <= 0) {
			indiciesToRemove.push_back(i);
		}
		else {
			this->caltropEffectPairList[i + 1] = framesToLive;
		}
	}

	int initial = indiciesToRemove.size() - 1;
	//Going in reverse to remove issues of earlier indicies being removed causing the indicies of later elements to change
	//[1,2,3,4,5] 4 is at index 3
	//[1,2,4,5] 4 is at index 2
	//This would make the indicies in the vector invalid
	for (int i = initial; i > -1; i--) {

		int index = indiciesToRemove[i];

		//Erase the caltropId
		this->caltropEffectPairList.erase(this->caltropEffectPairList.begin() + index);

		//Erase the frame counter that is now 0 that winds up in the same position
		this->caltropEffectPairList.erase(this->caltropEffectPairList.begin() + index);
	}
}

void Vehicle::takeBulletDamage(double dmgAmount) {
	this->health.takeDamageFromBullet(dmgAmount);
}

//adds one ability point
void Vehicle::pickup() {
	//now set the max ability at 9
	if (ability == 9)
		;
	else
		++ability;

	std::cout << "ability:" << ability << std::endl;
}

//ammo pickup, increases ammo by 1 to a max of 10
void Vehicle::ammo()
{
	turret.recharge();
}

//drops caltrops and adds the newly added caltrop to the given list
void Vehicle::useCaltrops(std::list<Caltrops*> *catropsList, float duration, PxScene* gScene, PxPhysics* gPhysics, PxVec3 position) {
	if (ability == 0 || affectedBySmoke)
		return;

	std::cout << "\nAbility Points: " << ability;

	PxVec3 pos = GetPosition();

	Caltrops* caltrop = new Caltrops(ID, duration);
	caltrop->createCaltrops(glm::vec3(pos.x, pos.y, pos.z));
	catropsList->push_back(caltrop);

	PxBoxGeometry geometry(PxVec3(1.5f, 5.f, 1.5f));
	PxTransform transform(position, PxQuat(PxIDENTITY()));
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
	catropsList->back()->actor = actor;
	actor->setName(CALTROPS.c_str());
	PxShape* shape;
	actor->getShapes(&shape, 1);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	catropsList->back()->actor->userData = catropsList->back();

	gScene->addActor(*actor);

	--ability;

	this->deployCaltropsEffect.playSound();
}

void Vehicle::useOil(std::list<Oil*> *oilList, float duration, PxScene* gScene, PxPhysics* gPhysics, PxVec3 position) {
	if (ability == 0 || affectedBySmoke)
		return;

	std::cout << "\nAbility Points: " << ability;

	PxVec3 pos = GetPosition();

	Oil* oil = new Oil(ID, duration);
	oil->createOil(glm::vec3(pos.x, pos.y, pos.z));
	oilList->push_back(oil);

	PxBoxGeometry geometry(PxVec3(1.5f, 5.f, 1.5f));
	PxTransform transform(position, PxQuat(PxIDENTITY()));
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
	oilList->back()->actor = actor;
	actor->setName(OIL.c_str());
	PxShape* shape;
	actor->getShapes(&shape, 1);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	oilList->back()->actor->userData = oilList->back();

	gScene->addActor(*actor);

	--ability;
	this->deployOilEffect.playSound();
}

void Vehicle::useSmoke(std::list<Smoke*>* smokeList, float duration, PxScene* gScene, PxPhysics* gPhysics, PxVec3 position) {
	if (ability == 0 || affectedBySmoke)
		return;

	std::cout << "\nAbility Points: " << ability;

	PxVec3 pos = GetPosition();

	Smoke* smoke = new Smoke(ID, duration);
	smoke->createSmoke(glm::vec3(pos.x, pos.y, pos.z));
	smokeList->push_back(smoke);

	PxBoxGeometry geometry(PxVec3(1.5f, 5.f, 1.5f));
	PxTransform transform(position, PxQuat(PxIDENTITY()));
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, geometry, *material);
	smokeList->back()->actor = actor;
	actor->setName(SMOKE.c_str());
	PxShape* shape;
	actor->getShapes(&shape, 1);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	smokeList->back()->actor->userData = smokeList->back();

	gScene->addActor(*actor);

	--ability;
	this->deploySmokeEffect.playSound();
}

void Vehicle::enableSmokeEffect()
{
	affectedBySmoke = true;
	smokeStartTime = glfwGetTime();
	std::cout << "SMOKE ACTIVATED" << std::endl;
	this->takeTrapDamage(0.f);
}

void Vehicle::disableSmokeEffect()
{
	affectedBySmoke = false;
	std::cout << "SMOKE DEACTIVATED" << std::endl;
}

void Vehicle::updateSmoke()
{
	if ((smokeStartTime + smokeDuration <= currentTime) && affectedBySmoke) {
		disableSmokeEffect();
	}
}

void Vehicle::enableOilEffect()
{
	affectedByOil = true;
	oilStartTime = glfwGetTime();
	std::cout << "OIL ACTIVATED" << std::endl;

	actor->setMass(actor->getMass() * 0.3f);

	//basic spinout
	if(gVehicleInputData.getAnalogSteer() >= 0)
		actor->addTorque(PxVec3(0, 13000, 0), PxForceMode::eIMPULSE);
	else
		actor->addTorque(PxVec3(0, -13000, 0), PxForceMode::eIMPULSE);

	this->takeTrapDamage(0.f);
	
}

void Vehicle::disableOilEffect()
{
	affectedByOil = false;
	std::cout << "OIL DEACTIVATED" << std::endl;

	actor->setMass(actor->getMass() / 0.3f);
}

void Vehicle::updateOil()
{
	if (affectedByOil) {
		if (oilStartTime + oilDuration <= currentTime) {
			disableOilEffect();
		}
		
		//actor->addTorque(PxVec3(0, 300, 0), PxForceMode::eIMPULSE);
	}
	

}

void Vehicle::updateCurrentTime()
{
	currentTime = glfwGetTime();
}

