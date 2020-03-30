#include "AIShootingComponent.h"



AIShootingComponent::AIShootingComponent()
{
	wantToPlaceTrap = 0;
}

void AIShootingComponent::Tick(float deltaTime)
{
	AimAtTarget();
}

AIShootingComponent::AIShootingComponent(Vehicle * v)
{
	wantToPlaceTrap = 0;
	owner = v;
	abilityCooldownTime = 10.f;
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
				raycast_handler.determine_hit_AI(); //Determines if the target gets hit by AI or not
				lastFiredTime = glfwGetTime();
				//target->update_health();
			}
		}
		// Target not in view, find new target
		else {
			target = nullptr;
		}

		float currentTime = glfwGetTime();
		if (shouldUseAbility && owner->ability > 0 && (currentTime - lastAbilityTime) > abilityCooldownTime) {
			// This is the AI shooting component. Use this to call abilities
			auto shooting = owner->getShootingComponent();
			PxVec3 p(owner->GetPosition());
			wantToPlaceTrap = rand() % 3 + 1; // Choose random ability
			
			
			// Set random cooldown from 0 to 10 seconds
			//abilityCooldownTime = 10.f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
			//min 3 max 10
			lastAbilityTime = currentTime;
		}
		else {
			wantToPlaceTrap = -1;
		}
	}
}

void AIShootingComponent::SetVehicles(std::vector<Vehicle*> vehiclesToSet)
{
	vehicles = vehiclesToSet;
	raycast_handler.set_vehiclelist(vehiclesToSet);
}

Vehicle * AIShootingComponent::FindTarget()
{
	// See if any other vehicle is in range
	for (auto aVehicle : vehicles) {
		if (IsTargetInView(aVehicle) && aVehicle != owner) {
			//aVehicle->update_health();
			raycast_handler.set_Target(aVehicle);//Sets the target for the raycast
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


bool AIShootingComponent::IsVehicleBehind(Vehicle* aTarget)
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
