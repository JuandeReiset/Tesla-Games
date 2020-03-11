#pragma once
#include "DamagingObject.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Model.h"
#include "Material.h"
class Oil :
	public DamagingObject
{
public:
	Oil(int idInput);
	~Oil();

	physx::PxRigidActor* actor;
	int id;

	//model stuff
	void createOil(glm::vec3 carPos);														//create Oil model
	void renderOil();														//render Oil model
	void load(GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess);

	//if Oil still exist
	bool isDead();
	void updateTime();															//this may be inside the tick func

private:
	float life, birthTime, currentTime;											//each Oil can exist 5 sec, if currentTime - birthTime > life, then destroy the instance
	glm::vec3 position;															//the Oil of the caltrops
	Model oilObj;

	glm::mat4 model;															//model matrix
	GLuint uniformModel, uniformSpecularIntensity, uniformShininess;
	Material shinyMaterial;
};

