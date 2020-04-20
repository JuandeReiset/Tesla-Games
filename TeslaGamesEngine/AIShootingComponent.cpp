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
	abilityCooldownTime = 3.f + (7.f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
	lastAbilityTime = glfwGetTime();
}

void AIShootingComponent::Aim()
{    
	//std::cout << "AIMING METHOD REACHED" << std::endl;
	// Find a target
	/*
	if (!target) {
		target = FindTarget();
		//std::cout << "CURRENTLY FINDING TARGET" << std::endl;
	}
	*/
	//else {
		// Aim at target if it is in view
		target = FindTarget();
		if (target) {
			//std::cout << "THERE IS CURRENTLY A TARGET" << std::endl;
			if (AimAtTarget()) {
				FindAimingState();
				// Fire at target if aim is locked
				if (aimingState == AimingState::Locked) {
					//std::cout << "FIRE @ " << glfwGetTime() << std::endl;
					auto shooting = owner->getShootingComponent();
					auto pos = owner->GetPosition();
					// Setting ammo to 0 because of performance issues. Remove when those are fixed
					shooting->fire(glm::vec3(pos.x, pos.y, pos.z), uniformModel, uniformSpecular, uniformShininess, Shootdir.x, Shootdir.y, Shootdir.z);
					raycast_handler.determine_hit_AI(); //Determines if the target gets hit by AI or not
					lastFiredTime = glfwGetTime();
					//aimingState = AimingState::Reloading;
				}
			}
			// Target not in view, find new target
			else {

				target = nullptr;
			}
		}
	//}

	float currentTime = glfwGetTime();
	if (shouldUseAbility && owner->ability > 0 && (currentTime - lastAbilityTime) > abilityCooldownTime) {
		TrackDrivingPoint* currentTarget = &owner->curTarget;
		float angleToTurn = abs(racetrack->getAngleToTurnBy(currentTarget, owner));
		// This is the AI shooting component. Use this to call abilities
		auto shooting = owner->getShootingComponent();
		PxVec3 p(owner->GetPosition());
		
		if (angleToTurn > 25.f) {
			wantToPlaceTrap = 3; // Choose oil
		}
		else {
			wantToPlaceTrap = rand() % 2 + 1; // Choose random ability from smoke or caltrops
		}
			
		// Set random cooldown from 3 to 10 seconds
		abilityCooldownTime = 3.f + (7.f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
		lastAbilityTime = currentTime;
	}
	else {
		wantToPlaceTrap = -1;
	}
}

void AIShootingComponent::SetVehicles(std::vector<Vehicle*> vehiclesToSet)
{
	vehicles = vehiclesToSet;
	raycast_handler.set_vehiclelist(vehiclesToSet);
}

Vehicle * AIShootingComponent::FindTarget()
{
	Vehicle* aTarget = nullptr;

	// See if any other vehicle is in range
	for (auto aVehicle : vehicles) {
		if (IsTargetInView(aVehicle) && aVehicle != owner) {
			//aVehicle->update_health();
			raycast_handler.set_Target(aVehicle);//Sets the target for the raycast
			aTarget = aVehicle;
			break;
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

	return aTarget;
}


bool AIShootingComponent::IsVehicleBehind(Vehicle* aTarget)
{
	physx::PxVec3 toTarget = aTarget->GetPosition() - owner->GetPosition();
	// Get length to target too
	auto distance = toTarget.magnitude();
	toTarget.normalize();
	// Check that it stays within the cone in behind (-10 > 10)
	physx::PxVec3 backwardDirection = owner->GetTransform().q.getBasisVector2();
	backwardDirection *= -1.f;

	// Check if target is within an 80 degree cone in behind of vehicle
	if ((abs(acos(toTarget.dot(backwardDirection))) * (180.f / 3.14) < 10.f) && distance < 25.f) {
		return true;
	}

	return false;
}

bool AIShootingComponent::IsTargetInView(Vehicle* aTarget)
{
	physx::PxVec3 toTarget = aTarget->GetPosition() - owner->GetPosition();
	auto distance = toTarget.magnitude();
	toTarget.normalize();
	// TODO: Rotate aim direction towards target
	// Check that it stays within the cone in front (-40 > 40)
	physx::PxVec3 forwardDirection = owner->GetTransform().q.getBasisVector2();

	// Check if target is within an 80 degree cone in front of vehicle
	if (abs(acos(toTarget.dot(forwardDirection))) * (180.f / 3.14) < 35.f) {
		return true;
		
	}
	return false;
	
}

bool AIShootingComponent::IsReloading()
{
	
	float currentTime = glfwGetTime();
	//std::cout << "CURRENT TIME CATCHED BY GLFW is" << currentTime << std::endl;
	if (currentTime- lastFiredTime > 1.f) {
		std::cout << "DONE RELOADING" << std::endl;
		return false;
	}
	else {
		std::cout << "STILL RELOADING" << std::endl;
		std::cout <<"Current cooldown: " <<currentTime - lastFiredTime << std::endl;
		return true;
	}
}

void AIShootingComponent::FindAimingState()
{
	if (owner->getShootingComponent()->ammo <= 0) {
		aimingState = AimingState::NoAmmo;
		//std::cout << "VEHICLE HAS NO AMMO"<<std::endl;
	}
	else if (target = nullptr) {
		aimingState = AimingState::NoTarget;
		std::cout << "NO TARGET FOUND" << std::endl;
	}
	else if (IsReloading()) {
		aimingState = AimingState::Reloading;
		std::cout << "VEHICLE STILL RELOADING" << std::endl;
	}
	else {
		aimingState = AimingState::Locked;
		//std::cout << "VEHICLE READY TO SHOOT" << std::endl;
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
