#include "AIShootingComponent.h"



AIShootingComponent::AIShootingComponent()
{
}

void AIShootingComponent::Tick(float deltaTime)
{
	AimAtTarget();
}

AIShootingComponent::AIShootingComponent(Vehicle * v)
{
	owner = v;
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

void AIShootingComponent::SetVehicles(std::vector<Vehicle*> vehiclesToSet)
{
	vehicles = vehiclesToSet;
}

Vehicle * AIShootingComponent::FindTarget()
{
	// See if any other vehicle is in range
	for (auto aVehicle : vehicles) {
		// TODO: Check that it is not aiming at self (Might not need cause we raycast)
		if (IsTargetInView(aVehicle) && aVehicle != owner) {
			return aVehicle;
		}
	}

	return nullptr;
}

bool AIShootingComponent::IsTargetInView(Vehicle* aTarget)
{
	// TODO: Raycast in PhysX
	// Raycast in direction of target
	// If ray hits anything, see if that is the target
	// If yes, return true
	// Else return false
	return false;
}

void AIShootingComponent::FindAimingState()
{
	// TODO: Create functions to determine these
	bool isTurretMoving;
	bool isReloading;

	if (ammo <= 0) {
		aimingState = AimingState::NoAmmo;
	}
	else if (target = nullptr) {
		aimingState = AimingState::NoTarget;
	}
	else if (isReloading) {
		aimingState = AimingState::Reloading;
	}
	else if (isTurretMoving) {
		aimingState = AimingState::Aiming;
	}
	else {
		aimingState = AimingState::Locked;
	}
}

void AIShootingComponent::AimAtTarget()
{
	// Get current aim direction (Forward vector of turret)
	// Get direction to target (Target pos - owner pos)
	physx::PxVec3 toTarget = target->GetPosition() - owner->GetPosition();
	// TODO: Rotate aim direction towards target
	updateDirection(toTarget.x, toTarget.y, toTarget.z);

	std::cout << "Aiming at: " << toTarget.x << ", " << toTarget.y << ", " << toTarget.z << std::endl;
}

AIShootingComponent::~AIShootingComponent()
{
}
