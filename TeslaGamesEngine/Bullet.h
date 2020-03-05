#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "DamagingObject.h"
#include "Model.h"
#include "Material.h"



class Bullet:DamagingObject
{
public:
	Bullet();
	//~Bullet();

	//model stuff
	void createBullet(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float x, float y, float z);														//create caltrops model
	void renderBullet();														//render caltrops model

	//if caltrops still exist
	bool isDead();
	void updateTime();//this may be inside the tick func
	float Direction_x;
	float Direction_y;
	float Direction_z;
	

private:
	float life, birthTime, currentTime;											//each caltrop can exist 5 sec, if currentTime - birthTime > life, then destroy the instance
	glm::vec3 position;															//the position of the caltrops
	Model BulletObj;
	float bullet_speed;
	float shoot_distance_x;
	float shoot_distance_z;
	glm::mat4 model;															//model matrix
	
	GLuint uniformModel, uniformSpecularIntensity, uniformShininess;
	Material shinyMaterial;
};

