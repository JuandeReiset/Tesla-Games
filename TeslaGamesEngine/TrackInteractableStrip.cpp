#include "TrackInteractableStrip.h"
TrackInteractableStrip::TrackInteractableStrip() {};
TrackInteractableStrip::~TrackInteractableStrip() { this->listOfLanePoints.clear(); };

void TrackInteractableStrip::addLanePoint(float x, float y, float z, int status) {
	this->listOfLanePoints.push_back(std::make_unique<TrackDrivingPoint>(x, y, z, status));
}
void TrackInteractableStrip::setLaneStatus(int atIndex, int newStatus) {

	TrackDrivingPoint ref = *this->listOfLanePoints[atIndex];
	float pointX = ref.x;
	float pointY = ref.y;
	float pointZ = ref.z;

	this->clearLaneStatus(atIndex);
	//TODO:
	//Stephen plz
	if (newStatus == trackInteractableObjects::AMMO_PICKUP) {

	}
	else if (newStatus == trackInteractableObjects::TESLA_PICKUP) {

	}
	else if (newStatus == trackInteractableObjects::CALTROPS) {

	}
	else if (newStatus == trackInteractableObjects::OIL) {

	}
	else if (newStatus == trackInteractableObjects::SMOKE) {

	}
	
	ref.switchAction(newStatus);
}
void TrackInteractableStrip::clearLaneStatus(int atIndex) {
	TrackDrivingPoint ref = *this->listOfLanePoints[atIndex];
	int oldAction = ref.actionToTake;

	//Remove status or something
	//TODO: Stephen plz
	if (oldAction == trackInteractableObjects::AMMO_PICKUP) {

	}
	else if (oldAction == trackInteractableObjects::TESLA_PICKUP) {

	}
	else if (oldAction == trackInteractableObjects::CALTROPS) {

	}
	else if (oldAction == trackInteractableObjects::OIL) {

	}
	else if (oldAction == trackInteractableObjects::SMOKE) {

	}
}