#pragma once
#include <vector>
#include <memory>
#include "TrackDrivingPoint.h"

class TrackInteractableStrip
{
	public:
		TrackInteractableStrip();
		~TrackInteractableStrip();
		void addLanePoint(float x, float y, float z, int status);
		void setLaneStatus(int atIndex, int newStatus);
		void clearLaneStatus(int atIndex);
		//A lane is basically a car width, so really how many cars can fit on a strip of track
		std::vector<std::unique_ptr<TrackDrivingPoint>> listOfLanePoints;
};

