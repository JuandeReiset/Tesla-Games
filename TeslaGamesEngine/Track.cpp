#include "Track.h"

Track::Track() {}
Track::~Track() {}
void Track::addPointToList(float x, float y, float z, int action) {
	this->listOfPoints.push_back(std::make_unique<TrackDrivingPoint>(x, y, z, action));
}

void Track::performMove(Vehicle* v) {
	TrackDrivingPoint* pastTarget = &v->pastTarget;
	TrackDrivingPoint* currentTarget = &v->curTarget;

	int pastAction = pastTarget->actionToTake;
	int currentAction = currentTarget->actionToTake;

	PxU32 curGear = v->gVehicle4W->mDriveDynData.getCurrentGear();
	float angleToTurn = getAngleToTurnBy(currentTarget, v);

	if (pastAction == trackDrivingPointActions::START && currentAction == trackDrivingPointActions::SLOW_DOWN) {
		if (std::abs(angleToTurn) < 5.f) {
			v->turn(0.f);
			v->forwards(1.f);
			v->reverse(0.f);
		}
		else {
			if (std::abs(angleToTurn) < 15.f) {
				v->forwards(0.5f);
				if (curGear <= PxVehicleGearsData::eTHIRD) {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-0.2f);
					}
					else {
						v->turn(0.2f);
					}
				}
				else {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-0.4f);
					}
					else {
						v->turn(0.4f);
					}
				}
			}
			else if (std::abs(angleToTurn) < 30.f) {
				v->forwards(0.5f);
				if (curGear <= PxVehicleGearsData::eTHIRD) {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-0.4f);
					}
					else {
						v->turn(0.4f);
					}
				}
				else {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-0.6f);
					}
					else {
						v->turn(0.6f);
					}
				}
			}
			else if (std::abs(angleToTurn) < 45.f) {
				v->forwards(0.5f);
				if (curGear <= PxVehicleGearsData::eTHIRD) {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-0.6f);
					}
					else {
						v->turn(0.6f);
					}
				}
				else {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-0.8f);
					}
					else {
						v->turn(0.8f);
					}
				}
			}
			else if (std::abs(angleToTurn) <= 90.f) {
				v->forwards(0.5f);
				if (curGear <= PxVehicleGearsData::eTHIRD) {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-0.8f);
					}
					else {
						v->turn(0.8f);
					}
				}
				else {
					if (angleToTurn < 0) {
						//turn left
						v->turn(-1.f);
					}
					else {
						v->turn(1.f);
					}
				}
			}
			else {
				float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());

				//For the cases where vehcile is spiining out, cuz why else would you be more than 90 degrees from a point
				if (sideways > 1.4f) {
					v->turn(0.f);
					v->reverse(0.f);
					v->forwards(0.f);
				}
				else {
					v->forwards(1.f);
					if (angleToTurn < 0) {
						v->turn(-1.f);
					}
					else {
						v->turn(1.f);
					}
				}
			}
		}
	}
	else {
		v->forwards(0.f);
		v->reverse(1.f);
		v->turn(0.f);
	}

	
}

// Return value of negative means left turn, postive means right turn
float Track::getAngleToTurnBy(TrackDrivingPoint* currentTarget, Vehicle* v) {
	float angle = 0.f;

	PxVec3 target = PxVec3(currentTarget->x, currentTarget->y, currentTarget->z);

	PxQuat vehicleQuaternion = v->GetTransform().q;
	PxVec3 vehiclePosition = v->GetPosition();

	PxVec3 vehicleFront = vehicleQuaternion.getBasisVector2();
	PxVec3 vehicleFrontNormal = vehicleFront.getNormalized();

	PxVec3 vecToFollow = target - vehiclePosition;
	PxVec3 vecToFollowNormal = vecToFollow.getNormalized();

	
	angle = acos(vehicleFrontNormal.dot(vecToFollowNormal));
	angle = angle * (180.f / M_PI);

	//This tries to turn left
	PxVec3 vehicleLeft = vehicleQuaternion.getBasisVector0();
	PxVec3 vehicleLeftNormal = vehicleLeft.getNormalized();
	float leftDot = vehicleLeftNormal.dot(vecToFollowNormal);

	if (leftDot > 0) {
		angle = -1 * angle;
	}
	
	
	return angle;
}