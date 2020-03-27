#include "Raycast_shooting.h"

Raycast_shooting::Raycast_shooting(std::vector<Vehicle*> listvehicles) {
	this->vehicles = listvehicles;
}

void Raycast_shooting::determine_hit(glm::vec3 startpos, glm::vec3 Dir) {

	for (auto aVehicle : vehicles) {
		if (is_in_direction(aVehicle) && aVehicle != owner) {
			
		}
	}
	
}

bool Raycast_shooting::is_in_direction(Vehicle* target) {
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
		//Shootdir = glm::vec3(toTarget.x, toTarget.y, toTarget.z);
		return true;
	}
	else {
		target = nullptr;
		return false;

	}
}
void Raycast_shooting::handle_hit(Vehicle v1) {
	v1.update_health();
}
