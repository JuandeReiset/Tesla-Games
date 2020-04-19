#include "Raycast_shooting.h"

Raycast_shooting::Raycast_shooting() {
	
}
void Raycast_shooting::set_vehiclelist(std::vector<Vehicle*> vehiclesToSet) {
	vehicles = vehiclesToSet;
}

void Raycast_shooting::determine_hit(glm::vec3 startpos, glm::vec3 Dir) {

	for (auto aVehicle : vehicles) {
		//std::cout << "There is Vehicles in the list" << std::endl;
		if (owner->getShootingComponent()->is_there_ammo()) {
			if (is_in_direction(aVehicle, Dir) && aVehicle != owner) {
			
				handle_hit(aVehicle);
				std::cout << "ENEMY VEHICLE HIT" << std::endl;
				//break;
			}
		}
	}
	
}

void Raycast_shooting::determine_hit_AI() {

		handle_hit(target_vehicle);

}

bool Raycast_shooting::is_in_direction(Vehicle* possible_target,glm::vec3 Shootdir) {
	// Get current aim direction (Forward vector of turret)
	// Get direction to target (Target pos - owner pos)
	physx::PxVec3 targetcurrentposition = possible_target->GetPosition();
	
	physx::PxVec3 toTarget = physx::PxVec3 (Shootdir.x,Shootdir.y,Shootdir.z);
	toTarget.normalize();
	glm::vec3 tcp = glm::vec3(targetcurrentposition.x, targetcurrentposition.y, targetcurrentposition.z); //target current position in world
	float rayLength = 200.f; //The length of the raycast ray

	physx::PxVec3 fineRayEnd = owner->GetPosition();  //point of the raycast
	float travelled = 0.0;						// how far we've walked across the whole ray when we cross over the terrain the first time
	bool intersectionFound = false;				// result that we send back
	float vehicle_bounds_z = 4.5f;
	float vehicle_bounds_y = 4.5f;
	float vehicle_bounds_x = 3.f;
	while (!intersectionFound && travelled <= rayLength)
	{
		travelled += 1.f;
		fineRayEnd += toTarget * 1.f;
		//std::cout << "Evaluating raycast: Pos X " << fineRayEnd.x << " Pos Y " << fineRayEnd.y << "Pos Z " << fineRayEnd.z << std::endl;
		// raycast between those two points using a binary search
		if (fineRayEnd.x > tcp.x-vehicle_bounds_x && fineRayEnd.x < tcp.x +vehicle_bounds_x)
		{
			if (fineRayEnd.y > tcp.y - vehicle_bounds_y && fineRayEnd.y < tcp.y + vehicle_bounds_y)
			{
				if (fineRayEnd.z > tcp.z - vehicle_bounds_z && fineRayEnd.z < tcp.z + vehicle_bounds_z)
				{
					intersectionFound = true;
					//std::cout << "HIT INTERSECTIONS" << std::endl;
					//std::cout << "iNTERSECTION FOUND AT: Pos X " << fineRayEnd.x << " Pos Y " << fineRayEnd.y << "Pos Z " << fineRayEnd.z << std::endl;
					//std::cout << "The Target vehicle position was at: Pos X " << tcp.x << " Pos Y " << tcp.y << "Pos Z " << tcp.z << std::endl << std::endl<< std::endl;
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
