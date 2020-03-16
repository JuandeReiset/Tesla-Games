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
		void pastStartCurrentSlowdown(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastTurnExitCurrentSlowDown(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastTurnExitCurrentStart(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastSlowDownCurrentTurnIn(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastTurnInCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastMajorCurrentExit(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastTurnInCurrentMinor(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastMinorCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastMajorCurrentMinor(PxU32 curGear, float angleToTurn, Vehicle * v);
		void pastMinorCurrentExit(PxU32 curGear, float angleToTurn, Vehicle * v);
		float getAngleToTurnBy(TrackDrivingPoint * currentTarget, Vehicle * v);
		std::vector<std::unique_ptr<TrackDrivingPoint>> listOfPoints;
};

