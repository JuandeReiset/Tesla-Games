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
	void Tick(float deltaTime);
	AIShootingComponent(Vehicle* v);

	void Aim();
	void SetVehicles(std::vector<Vehicle*> vehiclesToSet);

	// TODO: Remove. This is for testing
	void SetTarget(Vehicle* v) { target = v; }

	~AIShootingComponent();

private:
	Vehicle* FindTarget();
	bool IsTargetInView(Vehicle* aTarget);
	void FindAimingState();
	void AimAtTarget();

	std::vector<Vehicle*> vehicles;
	Vehicle* owner;
	Vehicle* target;
	AimingState aimingState;
	float threshold;
};

