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
		if (AimAtTarget()) {
			FindAimingState();
			// Fire at target if aim is locked
			if (aimingState == AimingState::Locked) {
				//std::cout << "FIRE @ " << glfwGetTime() << std::endl;
				auto shooting = owner->getShootingComponent();
				auto pos = owner->GetPosition();
				// Setting ammo to 0 because of performance issues. Remove when those are fixed
				shooting->fire(glm::vec3(pos.x, pos.y, pos.z), uniformModel, uniformSpecular, uniformShininess,Shootdir.x,Shootdir.y,Shootdir.z);
				lastFiredTime = glfwGetTime();
				//target->update_health();
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
		if (IsTargetInView(aVehicle) && aVehicle != owner) {
			aVehicle->update_health();
			return aVehicle;
		}
	}

	return nullptr;
}

bool AIShootingComponent::IsTargetInView(Vehicle* aTarget)
{
	physx::PxVec3 toTarget = aTarget->GetPosition() - owner->GetPosition();
	toTarget.normalize();
	// TODO: Rotate aim direction towards target
	// Check that it stays within the cone in front (-40 > 40)
	physx::PxVec3 forwardDirection = owner->GetTransform().q.getBasisVector2();

	// Check if target is within an 80 degree cone in front of vehicle
	if (abs(acos(toTarget.dot(forwardDirection))) * (180.f / 3.14) < 40.f) {
		return true;
	}
	return false;
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

bool AIShootingComponent::AimAtTarget()
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
		Shootdir=glm::vec3(toTarget.x,toTarget.y,toTarget.z);
		return true;
	}
	else {
		target = nullptr;
		return false;
		
	}

	/*std::cout << "AIMING AT: " << toTarget.x << ", " << toTarget.y << ", " << toTarget.z << std::endl;*/
}

void AIShootingComponent::SetUniformLocations(GLuint model, GLuint spec, GLuint shine)
{
	uniformModel = model;
	uniformSpecular = spec;
	uniformShininess = shine;
}

AIShootingComponent::~AIShootingComponent()
{
}
