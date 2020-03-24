#pragma once
namespace trackInteractableObjects {
	const int EMPTY = -1;
	const int AMMO_PICKUP = -2;
	const int TESLA_PICKUP = -3;
	const int CALTROPS = -4;
	const int OIL = -5;
	const int SMOKE = -6;
}

namespace trackDrivingPointActions
{
	const int START = 0;
	const int SLOW_DOWN = 1;
	const int TURN_IN = 2;
	const int APEX_MINOR = 3;
	const int APEX_MAJOR = 4;
	const int TURN_EXIT = 5;
	const int START_LINE = 6;
}

class TrackDrivingPoint
{
	public:
		friend bool operator== (TrackDrivingPoint & lhs, TrackDrivingPoint & rhs);
		TrackDrivingPoint();
		TrackDrivingPoint(float x, float y, float z, int action);
		~TrackDrivingPoint();
		void switchAction(int newAction);
		float x;
		float y;
		float z;
		int actionToTake;
		float pointDistanceLimit = 15.f;
};

