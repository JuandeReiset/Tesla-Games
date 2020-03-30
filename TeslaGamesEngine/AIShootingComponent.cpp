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
	// Set a random interval of using abilities from 0 to 10 seconds
	abilityCooldownTime = 10.f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
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
				std::cout << "FIRE @ " << glfwGetTime() << std::endl;
				auto shooting = owner->getShootingComponent();
				auto pos = owner->GetPosition();
				// Setting ammo to 0 because of performance issues. Remove when those are fixed
				shooting->ammo = 0;
				shooting->fire(glm::vec3(pos.x, pos.y, pos.z), uniformModel, uniformSpecular, uniformShininess);
				lastFiredTime = glfwGetTime();
			}
		}
		// Target not in view, find new target
		else {
			target = nullptr;
		}
	}

	if (shouldUseAbility && (glfwGetTime() -lastAbilityTime) > abilityCooldownTime) {
		// This is the AI shooting component. Use this to call abilities
		auto shooting = owner->getShootingComponent();
		PxVec3 p(owner->GetPosition());
		int abilityToUse = rand() % 3 + 1; // Choose random ability
		switch (abilityToUse) {
		case 1:
			// Use caltrops
			// physEng->createCaltropsTriggerVolume(p.x, p.y, p.z, 5.f, // Their id);
			break;
		case 2:
			// Use oil
			// physEng->createOilTriggerVolume(p.x, p.y, p.z, 5.f, // Their id);
			break;
		case 3:
			// Use smoke
			// physEng->createSmokeTriggerVolume(p.x, p.y, p.z, 5.f, // Their id);
			break;
		}
		// Set random cooldown from 0 to 10 seconds
		abilityCooldownTime = 10.f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
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
			return aVehicle;
		}
	}
		
	// See if there is a vehicle behind you
	shouldUseAbility = false;
	for (auto aVehicle : vehicles) {
		if (IsVehicleBehind(aVehicle)) {
			shouldUseAbility = true;
			break;
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

bool AIShootingComponent::IsVehicleBehind(Vehicle * aTarget)
{
	physx::PxVec3 toTarget = aTarget->GetPosition() - owner->GetPosition();
	toTarget.normalize();
	// Check that it stays within the cone in front (-40 > 40)
	physx::PxVec3 backwardDirection = owner->GetTransform().q.getBasisVector2();
	backwardDirection *= -1.f;

	// Check if target is within an 80 degree cone in behind of vehicle
	if (abs(acos(toTarget.dot(backwardDirection))) * (180.f / 3.14) < 40.f) {
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
