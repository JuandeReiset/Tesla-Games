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
#include "Bullet.h"
#include "AudioEngine.h"

#include <list>

class ShootComp :
	public Component
{
	public:
		ShootComp();
		
		void initShootCompAudio(AudioEngine* audioEngine);
		//model stuff

		//Add an bullet object and required rendering settings to a vector
		void addBullet_toList(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float x, float y, float z);
		void addBullet_toList(GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess);
		//method to pass all bullet objects to rendering
		void renderAllBullets();														//render caltrops model

		//update position of vehicle and direction which it is facing
		void updatePosition(glm::vec3 newpos);
		void updateAudioPosition(float x, float y, float z);
		void updateDirection(float x, float y, float z);

		//not sure how to use this yet
		void Tick(float deltaTime);

		//decrease ammo by 1
		void fire();

		// increase ammo by 10
		void recharge();

		//evaluates if there is still ammo in the turret
		bool is_there_ammo();

		//holds all the bullets to be rendered
		std::list<Bullet> bulletsList;


		//if bullet still exist
	
		void updateTime();//this may be inside the tick func

		//parameters for the Direction vector
		float Direction_x;
		float Direction_y;
		float Direction_z;

		// Stores current vehicle position
		glm::vec3 start_position;

		int ammo;
	private:
		float life, birthTime, currentTime;											//each caltrop can exist 5 sec, if currentTime - birthTime > life, then destroy the instance
																	//the position of the caltrops
		//Model BulletObj;
		float bullet_speed=0.8f;
		AudioEngine* audioEngine;
		AudioBoomBox shootSound;
		//float shoot_distance_x;
		//float shoot_distance_z;
		//glm::mat4 model;
		

		GLuint uniformModel, uniformSpecularIntensity, uniformShininess;
		Material shinyMaterial;
	};

