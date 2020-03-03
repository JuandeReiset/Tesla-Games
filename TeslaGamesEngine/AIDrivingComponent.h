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
	~AIDrivingComponent();

private:
	void MoveTo(DrivingTarget);

	std::vector<DrivingTarget> drivingTargets;
	int currentTargetIndex;
	Vehicle* owner;
	
	float threshold = 0.1f;
};

