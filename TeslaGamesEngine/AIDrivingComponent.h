#pragma once
#include "Component.h"
#include "Vehicle.h"
#include <vector>
#include <math.h>   

struct DrivingTarget {
	float x;
	float y;
};
class AIDrivingComponent :
	public Component
{
public:
	AIDrivingComponent();
	AIDrivingComponent(Vehicle* v);
	void Tick(float deltaTime);
	void AddDrivingTarget(DrivingTarget toAdd);
	void AddDrivingTarget(float x, float y);
	~AIDrivingComponent();

private:
	void MoveTo(DrivingTarget);

	std::vector<DrivingTarget> drivingTargets;
	int currentTargetIndex = 0;
	Vehicle* owner;
	
	float threshold = 20.0f;
};

