#pragma once
namespace trackDrivingPointActions
{
	const int START = 0;
	const int SLOW_DOWN = 1;
	const int TURN_IN = 2;
	const int APEX_MINOR = 3;
	const int APEX_MAJOR = 4;
	const int TURN_EXIT = 5;
}

class TrackDrivingPoint
{
	public:
		TrackDrivingPoint();
		TrackDrivingPoint(float x, float y, float z, int action);
		~TrackDrivingPoint();
		float x;
		float y;
		float z;
		int actionToTake;
		float pointDistanceLimit = 15.f;
};

