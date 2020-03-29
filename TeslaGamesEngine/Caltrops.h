#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "DamagingObject.h"
#include "Model.h"
#include "Material.h"

class Caltrops:DamagingObject
{
public:
	Caltrops(int idInput, float duration);
	~Caltrops();

	physx::PxRigidActor* actor;
	int id;

	//model stuff
	void createCaltrops(glm::vec3 carPos);														//create caltrops model
	void renderCaltrops();														//render caltrops model
	void load(GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess);

	//if caltrops still exist
	bool isDead();
	void updateTime();															//this may be inside the tick func

private:
	float life, birthTime, currentTime;											//each caltrop can exist 5 sec, if currentTime - birthTime > life, then destroy the instance
	glm::vec3 position;															//the position of the caltrops
	Model caltropsObj;

	glm::mat4 model;															//model matrix
	GLuint uniformModel, uniformSpecularIntensity, uniformShininess;
	Material shinyMaterial;
};

