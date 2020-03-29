#include "Raycast_shooting.h"

Raycast_shooting::Raycast_shooting() {
	
}
void Raycast_shooting::set_vehiclelist(std::vector<Vehicle*> vehiclesToSet) {
	vehicles = vehiclesToSet;
}

void Raycast_shooting::determine_hit(glm::vec3 startpos, glm::vec3 Dir) {

	for (auto aVehicle : vehicles) {
		std::cout << "There is Vehicles in the list" << std::endl;
		if (is_in_direction(aVehicle) && aVehicle != owner) {
			handle_hit(aVehicle);
			std::cout << "PLAYER SHOT VEHICLE" << std::endl;
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
	physx::PxVec3 tcp = possible_target->GetPosition();
	
	physx::PxVec3 toTarget = possible_target->GetPosition() - owner->GetPosition();
	glm::vec3 targetcurrentpos = glm::vec3(tcp.x, tcp.y, tcp.z);
	float rayLength = 200.f; //The length of the raycast ray

	physx::PxVec3 fineRayEnd = owner->GetPosition();  //Beginning position for raycasting
	float travelled = 0.0;						// how far we've walked across the whole ray when we cross over the terrain the first time
	bool intersectionFound = false;				// result that we send back

	while (!intersectionFound && travelled <= rayLength)
	{
		travelled += 2.f;
		fineRayEnd += toTarget * 2.f;

		// raycast between those two points using a binary search
		if (fineRayEnd.y > -100)
		{
			///fineRayStart = fineRayEnd - forward * squareSize;
			intersectionFound = true;
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
void Raycast_shooting::set_STARTPOS(glm::vec3 sp) {
	Start_pos = sp;
}
void Raycast_shooting::set_Target(Vehicle* target) {
	target_vehicle = target;
}
