#pragma once
#include "ShootComp.h"
#include "Vehicle.h"


enum class AimingState
{
	Reloading,
	NoTarget,
	Aiming,
	Locked,
	NoAmmo
};

class AIShootingComponent :
	public ShootComp
{
public:
	AIShootingComponent();

	void Aim();

	~AIShootingComponent();

private:
	Vehicle* FindTarget();
	bool IsTargetInView(Vehicle* aTarget);
	AimingState FindAimingState();
	void AimAtTarget();

	std::vector<Vehicle*> vehicles;
	Vehicle* target;
	AimingState aimingState;
	float threshold;
};

