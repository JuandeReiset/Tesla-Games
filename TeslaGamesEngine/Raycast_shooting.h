#pragma once

#include "Vehicle.h"
#include <vector>
#include <glm\glm.hpp>

class Raycast_shooting
{
public:


private:
	glm::vec3 Start_pos;
	glm::vec3  Ray_direction;

	std::vector<Vehicle*> vehicles;
	Vehicle* owner;
	Vehicle* target;
   
};

