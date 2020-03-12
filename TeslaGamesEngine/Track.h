#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <vector>
#include <memory>
#include <math.h>
#include "Vehicle.h"

class Track
{
	public:
		Track();
		~Track();
		void addPointToList(float x, float y, float z, int action);
		void performMove(Vehicle * v);
		float getAngleToTurnBy(TrackDrivingPoint * currentTarget, Vehicle * v);
		std::vector<std::unique_ptr<TrackDrivingPoint>> listOfPoints;
};

