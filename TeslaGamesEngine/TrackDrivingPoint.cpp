#include "TrackDrivingPoint.h"
TrackDrivingPoint::TrackDrivingPoint(float x, float y, float z, int action) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->actionToTake = action;
}
TrackDrivingPoint::TrackDrivingPoint() {}
TrackDrivingPoint::~TrackDrivingPoint() {}

bool operator==(TrackDrivingPoint & lhs, TrackDrivingPoint & rhs)
{
	bool x = lhs.x == rhs.x;
	bool y = lhs.y == rhs.y;
	bool z = lhs.z == rhs.z;
	bool action = lhs.actionToTake == rhs.actionToTake;

	return x && y && z && action;
}

void TrackDrivingPoint::switchAction(int newAction) {
	this->actionToTake = newAction;
}
