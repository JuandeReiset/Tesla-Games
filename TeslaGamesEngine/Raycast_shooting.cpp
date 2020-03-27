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
	physx::PxVec3 toTarget = target->GetPosition() - owner->GetPosition();
	toTarget.normalize();
}
void Raycast_shooting::handle_hit(Vehicle v1) {

}
