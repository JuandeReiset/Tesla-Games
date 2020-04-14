#pragma once
#include "DamagingObject.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Model.h"
#include "Material.h"
class Smoke :
	public DamagingObject
{
public:
	Smoke(int idInput, float duration);
	~Smoke();

	physx::PxRigidActor* actor;
	int id;

	//model stuff
	void createSmoke(glm::vec3 carPos);														//create smoke model
	void renderSmoke();														//render smoke model
	void load(GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess);

	//if smoke still exist
	bool isDead();
	void updateTime();															//this may be inside the tick func

private:
	float life, birthTime, currentTime;											//each smoke can exist 5 sec, if currentTime - birthTime > life, then destroy the instance
	glm::vec3 position;															//the position of the smoke
	Model smokeObj;
	Model tracksmokeObj;

	glm::mat4 model;															//model matrix
	GLuint uniformModel, uniformSpecularIntensity, uniformShininess;
	Material shinyMaterial;
};

