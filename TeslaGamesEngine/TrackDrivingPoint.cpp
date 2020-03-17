#include "TrackDrivingPoint.h"
TrackDrivingPoint::TrackDrivingPoint(float x, float y, float z, int action) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->actionToTake = action;
}
TrackDrivingPoint::TrackDrivingPoint() {}
TrackDrivingPoint::~TrackDrivingPoint() {}