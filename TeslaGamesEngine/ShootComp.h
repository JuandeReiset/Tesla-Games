#pragma once
#include "Component.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "DamagingObject.h"
#include "Model.h"
#include "Material.h"

class ShootComp :
	public Component
{
	public:
		ShootComp();
		~ShootComp();

		//model stuff
		void createBullet(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float x, float y, float z);														//create caltrops model
		void renderBullet();														//render caltrops model
		void updatePosition(glm::vec3 newpos);
		void Tick(float deltaTime);
		void fire();
		bool is_there_ammo();

		//if bullet still exist
		bool isDead();
		void updateTime();//this may be inside the tick func
		float Direction_x;
		float Direction_y;
		float Direction_z;
		int ammo;
		glm::vec3 position;
	private:
		float life, birthTime, currentTime;											//each caltrop can exist 5 sec, if currentTime - birthTime > life, then destroy the instance
																	//the position of the caltrops
		Model BulletObj;
		float bullet_speed;
		float shoot_distance_x;
		float shoot_distance_z;
		glm::mat4 model;
		

		GLuint uniformModel, uniformSpecularIntensity, uniformShininess;
		Material shinyMaterial;
	};

