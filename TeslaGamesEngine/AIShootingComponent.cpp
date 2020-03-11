#include "AIShootingComponent.h"



AIShootingComponent::AIShootingComponent()
{
}

void AIShootingComponent::Aim()
{
	// Find a target
	if (!target) {
		target = FindTarget();
	}
	else {
		// Aim at target if it is in view
		if (IsTargetInView(target)) {
			AimAtTarget();
			FindAimingState();
			// Fire at target if aim is locked
			if (aimingState == AimingState::Locked) {
				fire();
			}
		}
		// Target not in view, find new target
		else {
			target = nullptr;
		}
	}
}

Vehicle * AIShootingComponent::FindTarget()
{
	//	Go through all vehicles
	//	if(IsTargetInView(aVehicle))
	//		return aVehicle
	
	// See if any other vehicle is in range
	for (auto aVehicle : vehicles) {
		// TODO: Check that it is not aiming at self
		if (IsTargetInView(aVehicle)) {
			return aVehicle;
		}
	}

	return nullptr;
}

bool AIShootingComponent::IsTargetInView(Vehicle* aTarget)
{
	return false;
}

AimingState AIShootingComponent::FindAimingState()
{
	// TODO: Create functions to determine these
	bool isTurretMoving;
	bool isReloading;

	if (ammo <= 0) {
		return AimingState::NoAmmo;
	}
	else if (target = nullptr) {
		return AimingState::NoTarget;
	}
	else if (isReloading) {
		return AimingState::Reloading;
	}
	else if (isTurretMoving) {
		return AimingState::Aiming;
	}
	else {
		return AimingState::Locked;
	}
}

void AIShootingComponent::AimAtTarget()
{
	// Get current aim direction
	// Get direction to target
	// Rotate aim direction towards target
}

AIShootingComponent::~AIShootingComponent()
{
}
