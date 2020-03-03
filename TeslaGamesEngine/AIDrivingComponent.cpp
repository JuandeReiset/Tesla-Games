#include "AIDrivingComponent.h"



AIDrivingComponent::AIDrivingComponent()
{
}

AIDrivingComponent::AIDrivingComponent(Vehicle * v)
{
	owner = v;
}

void AIDrivingComponent::Tick(float deltaTime)
{
	// Move to current target
	DrivingTarget currentTarget = drivingTargets[currentTargetIndex];
	MoveTo(currentTarget);

	// Increment target if current target is close enough
	physx::PxVec3 currentPos = owner->GetPosition();
	float distance = sqrt(((currentPos.x - currentTarget.x) * (currentPos.x - currentTarget.x)) + ((currentPos.z - currentTarget.y) * (currentPos.z - currentTarget.y)));
	if (distance < threshold) {
		if (currentTargetIndex < drivingTargets.size() - 1) {
			currentTargetIndex++;
		}
		else {
			currentTargetIndex = 0;
		}
	}
}

void AIDrivingComponent::AddDrivingTarget(DrivingTarget toAdd)
{
	drivingTargets.push_back(toAdd);
}

void AIDrivingComponent::MoveTo(DrivingTarget)
{
	// Get current position
	physx::PxVec3 currentPos = owner->GetPosition(); 

	// Get current direction
	physx::PxVec3 forwardDirection = owner->GetTransform().q.getBasisVector1();

	// Get angle between current direction and position to target
	DrivingTarget currentTarget = drivingTargets[currentTargetIndex];
	physx::PxVec3 toTarget = physx::PxVec3(currentPos.x - currentTarget.x, currentPos.y, currentPos.z - currentTarget.y);
	toTarget.normalize();

	float angle = acos(toTarget.dot(forwardDirection));

	// Apply turn magnitude based on difference in 2 angles (Max rotation when its directly behind you)
	float turnMagnitude = angle / 180.f;
	owner->turn(turnMagnitude);

	// Go faster if not turning
	owner->forwards(1.0f - turnMagnitude); 
}

AIDrivingComponent::~AIDrivingComponent()
{
}