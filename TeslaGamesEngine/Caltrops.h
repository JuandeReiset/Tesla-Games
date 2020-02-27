#pragma once

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "DamagingObject.h"

class Caltrops:DamagingObject
{
public:
	Caltrops();
	~Caltrops();

	void createCaltrops();														//create caltrops model
	void renderCaltrops();														//render caltrops model

private:
	float life, birthTime, currentTime;											//each caltrop can exist 5 sec, if currentTime - birthTime > life, then destroy the instance
	glm::vec3 position;															//the position of the caltrops

};

