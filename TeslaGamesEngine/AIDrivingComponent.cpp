#include "AIDrivingComponent.h"
#include <iostream>



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
	std::cout << "Current Target: " << currentTarget.x << ", " << currentTarget.y << std::endl;
	
	physx::PxVec3 currentPos = owner->GetPosition();
	lastPos = currentPos;

	// Increment target if current target is close enough
	float distance = sqrt(((currentPos.x - currentTarget.x) * (currentPos.x - currentTarget.x)) + ((currentPos.z - currentTarget.y) * (currentPos.z - currentTarget.y)));
	
	if (distance < threshold) {
		std::cout << "Current Target: " << currentTarget.x << ", " << currentTarget.y << std::endl;
		currentTargetIndex++;
		
		if (currentTargetIndex >= drivingTargets.size() - 1) currentTargetIndex = 1;
	}

	float distanceMoved = sqrt(((currentPos.x - lastPos.x) * (currentPos.x - lastPos.x)) + ((currentPos.z - lastPos.y) * (currentPos.z - lastPos.y)));

}

void AIDrivingComponent::AddDrivingTarget(DrivingTarget toAdd)
{
	drivingTargets.push_back(toAdd);
}

void AIDrivingComponent::AddDrivingTarget(float x, float y)
{
	DrivingTarget toAdd;
	toAdd.x = x;
	toAdd.y = y;
	drivingTargets.push_back(toAdd);
}

// TODO: Blend between next point and the one after it ??
void AIDrivingComponent::MoveTo(DrivingTarget)
{
	// Get current position
	physx::PxVec3 currentPos = owner->GetPosition(); 

	// Get current direction
	physx::PxVec3 forwardDirection = owner->GetTransform().q.getBasisVector2();

	// Get angle between current direction and position to target
	DrivingTarget currentTarget = drivingTargets[currentTargetIndex];
	physx::PxVec3 toTarget = physx::PxVec3(currentTarget.x - currentPos.x, currentPos.y, currentTarget.y - currentPos.z);
	toTarget.normalize();

	float angle = acos(forwardDirection.dot(toTarget));
	angle *=-(180.f / 3.14159);

	// Apply turn magnitude based on difference in 2 angles
	float turnMagnitude = angle / 180.f;
	// turnMagnitude *= 0.5;
	owner->turn(turnMagnitude/2);

	// Go faster if not turning
	// TODO: Change this from set values to a curve for smoothing between turning/accelerating
	// TODO: Also add in an option for handbrakes
	float forwardsMagnitude = (1.0f - turnMagnitude)/2;
	if (forwardsMagnitude > 1.0f) forwardsMagnitude = 1.0f;
	if (abs(angle) > 75.f && owner->GetForwardsSpeed() > 60.f) {
		// Will be changed to handbrake after
		owner->reverse(1.0f);
	}
	else if (abs(angle) > 60.f) {
		forwardsMagnitude *= 0.33;
		owner->forwards(forwardsMagnitude);
	}
	else {
		owner->forwards(forwardsMagnitude);
	}

	// if (forwardsMagnitude < 0.0f) forwardsMagnitude = 0.0f;
	
	/*std::cout << "Forwards " << forwardsMagnitude << std::endl;
	std::cout << "Turn " << turnMagnitude << std::endl;*/
}


AIDrivingComponent::~AIDrivingComponent()
{
}