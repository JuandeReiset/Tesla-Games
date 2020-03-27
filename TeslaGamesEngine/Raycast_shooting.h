#pragma once

#include "Vehicle.h"
#include <vector>
#include <glm\glm.hpp>

class Raycast_shooting
{
public:
	Raycast_shooting(std::vector<Vehicle*> listvehicles);
	void determine_hit(glm::vec3 startpos, glm::vec3 Dir);
	bool is_in_direction(Vehicle* v);
	void handle_hit(Vehicle v1);

private:
	glm::vec3 Start_pos;
	glm::vec3  Ray_direction;

	std::vector<Vehicle*> vehicles;
	Vehicle* owner;
	Vehicle* target_vehicle;
   
};

