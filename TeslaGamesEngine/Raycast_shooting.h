#pragma once

#include "Vehicle.h"
#include <vector>
#include <glm\glm.hpp>

class Raycast_shooting
{
public:
	Raycast_shooting();
	void set_vehiclelist(std::vector<Vehicle*> vehiclesToSet);
	void determine_hit(glm::vec3 startpos, glm::vec3 Dir);
	void determine_hit_AI();
	bool is_in_direction(Vehicle* v);
	void handle_hit(Vehicle* v1);

	void set_Target(Vehicle* target);

private:
	glm::vec3 Start_pos;
	glm::vec3  Ray_direction;

	std::vector<Vehicle*> vehicles;
	Vehicle* owner;
	Vehicle* target_vehicle;
   
};

