#include "Raycast_shooting.h"

Raycast_shooting::Raycast_shooting() {
	
}
void Raycast_shooting::set_vehiclelist(std::vector<Vehicle*> vehiclesToSet) {
	vehicles = vehiclesToSet;
}

void Raycast_shooting::determine_hit(glm::vec3 startpos, glm::vec3 Dir) {

	for (auto aVehicle : vehicles) {
		//std::cout << "There is Vehicles in the list" << std::endl;
		if (is_in_direction(aVehicle) && aVehicle != owner) {
			if (owner->getShootingComponent()->is_there_ammo()) {
				handle_hit(aVehicle);
				
				//break;
			}
		}
	}
	
}

void Raycast_shooting::determine_hit_AI() {

	int iSecret = rand() % 10 + 1;

	if (iSecret > 2) {
		handle_hit(target_vehicle);
	}
	

}

bool Raycast_shooting::is_in_direction(Vehicle* possible_target) {
	// Get current aim direction (Forward vector of turret)
	// Get direction to target (Target pos - owner pos)
	physx::PxVec3 targetcurrentposition = possible_target->GetPosition();
	
	physx::PxVec3 toTarget = possible_target->GetPosition() - owner->GetPosition();
	glm::vec3 tcp = glm::vec3(targetcurrentposition.x, targetcurrentposition.y, targetcurrentposition.z); //target current position in world
	float rayLength = 200.f; //The length of the raycast ray

	physx::PxVec3 fineRayEnd = owner->GetPosition();  //point of the raycast
	float travelled = 0.0;						// how far we've walked across the whole ray when we cross over the terrain the first time
	bool intersectionFound = false;				// result that we send back

	while (!intersectionFound && travelled <= rayLength)
	{
		travelled += 2.f;
		fineRayEnd += toTarget * 2.f;

		// raycast between those two points using a binary search
		if (fineRayEnd.x > tcp.x-2.f && fineRayEnd.x < tcp.x +2.f)
		{
			if (fineRayEnd.y > tcp.y - 2.f && fineRayEnd.y < tcp.y + 2.f) {
				if (fineRayEnd.z > tcp.z - 2.f && fineRayEnd.z < tcp.z + 2.f) {
					intersectionFound = true;
					std::cout << "HIT INTERSECTIONS" << std::endl;
				}
			}
		}
	}
	return intersectionFound;
	
}
void Raycast_shooting::handle_hit(Vehicle* v1) {
	v1->update_health();
}

void Raycast_shooting::set_Owner(Vehicle* own) {
	owner = own;
}

void Raycast_shooting::set_Target(Vehicle* target) {
	target_vehicle = target;
}
