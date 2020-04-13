#include "TrackInteractableStrip.h"
TrackInteractableStrip::TrackInteractableStrip() {};
TrackInteractableStrip::~TrackInteractableStrip() { this->listOfLanePoints.clear(); };

void TrackInteractableStrip::addLanePoint(float x, float y, float z, int status, int lap) {
	this->listOfLanePoints.push_back(std::make_unique<TrackDrivingPoint>(x, y, z, status, lap));
}
void TrackInteractableStrip::setLaneStatus(int atIndex, int newStatus) {

	float pointX = this->listOfLanePoints[atIndex]->x;
	float pointY = this->listOfLanePoints[atIndex]->y;
	float pointZ = this->listOfLanePoints[atIndex]->z;

	this->clearLaneStatus(atIndex);
	//TODO:
	//Stephen plz
	//sets the list of points in the trip to these types

	//these change on a lap to lap basis
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
	
	this->listOfLanePoints[atIndex]->switchAction(newStatus);
}
void TrackInteractableStrip::clearLaneStatus(int atIndex) {
	int oldAction = this->listOfLanePoints[atIndex]->actionToTake;

	//Remove status or something
	//TODO: Stephen plz
	//resets the list of points, may not need these he just put these here for help
	//should just change points to empty
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