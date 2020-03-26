#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <vector>
#include <memory>
#include <math.h>
#include "Vehicle.h"
#include "TrackInteractableStrip.h"

namespace trackTypeConstants
{
	const int OVAL_TEST= -1;
	const int HYPERLOOP = 0;
	const int STARLINK = 1;
}
class Track
{
	public:
		Track();
		Track(int trackType);
		~Track();
		void addPointToList(float x, float y, float z, int action);
		void addStartPointToList(float x, float y, float z);
		void addInteractableStripToList();
		void initializeTrackPoints(int trackType);
		void performStuckCorrectionMove(Vehicle * v);
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
		std::vector<std::unique_ptr<TrackInteractableStrip>> listOfLaneStrips;
		std::vector<std::unique_ptr<TrackDrivingPoint>> listOfStartPoints;
};