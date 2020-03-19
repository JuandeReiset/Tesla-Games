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
				std::cout << "FIRE @ " << glfwGetTime() << std::endl;
				owner->getShootingComponent()->fire();
				lastFiredTime = glfwGetTime();
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
	Vehicle* v = nullptr;
	for (auto aVehicle : vehicles) {
		if (IsTargetInView(aVehicle) && aVehicle != owner) {
			v = aVehicle;
		}
	}

	return v;
}

bool AIShootingComponent::IsTargetInView(Vehicle* aTarget)
{
	// TODO: Raycast in PhysX
	// Raycast in direction of target
	// If ray hits anything, see if that is the target
	// If yes, return true
	// Else return false
	return true;
}

bool AIShootingComponent::IsReloading()
{
	if (glfwGetTime() - lastFiredTime > 1.f) {
		return false;
	}
	else {
		return true;
	}
}

void AIShootingComponent::FindAimingState()
{
	if (owner->getShootingComponent()->ammo <= 0) {
		aimingState = AimingState::NoAmmo;
	}
	else if (target = nullptr) {
		aimingState = AimingState::NoTarget;
	}
	else if (IsReloading()) {
		aimingState = AimingState::Reloading;
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
	toTarget.normalize();
	// TODO: Rotate aim direction towards target
	// Check that it stays within the cone in front (-40 > 40)
	physx::PxVec3 forwardDirection = owner->GetTransform().q.getBasisVector2();

	// Check if target is within an 80 degree cone in front of vehicle
	if (abs(acos(toTarget.dot(forwardDirection))) * (180.f / 3.14) < 40.f) {
		owner->getShootingComponent()->updateDirection(toTarget.x, toTarget.y, toTarget.z);
	}
	else {
		target = nullptr;
	}

	/*std::cout << "AIMING AT: " << toTarget.x << ", " << toTarget.y << ", " << toTarget.z << std::endl;*/
}

AIShootingComponent::~AIShootingComponent()
{
}
