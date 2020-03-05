#include "ShootComp.h"

ShootComp::ShootComp() {
	life = 5.f;											//lifetime is 5 sec
	birthTime = glfwGetTime();
	currentTime = glfwGetTime();

	ammo = 10;

	
	//model = glm::mat4(1.f);
	uniformModel = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;

	shinyMaterial = Material(4.0f, 256);
}
/*
bool ShootComp::isDead() {
	updateTime();
	if (currentTime - birthTime >= life)
		return true;
	else
		return false;
}
*/
void ShootComp::updateTime() {
	currentTime = glfwGetTime();
}
/*
void ShootComp::addBullet_toList(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float Dir_x, float Dir_y, float Dir_z) {
	
	fire();
	
	
	start_position = glm::vec3(carPos.x, carPos.y + 0.5f, carPos.z);
	//model = glm::translate(model, start_position);
	//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

	//bullet_speed = 0.2f;
	Direction_x = Dir_x;
	Direction_y = Dir_y;
	Direction_z = Dir_z;
	uniformModel = uniModel;
	uniformShininess = uniShininess;
	uniformSpecularIntensity = uniSpecularIntensity;

	//BulletObj.LoadModel("Models/bullet.obj");

	
}
*/
void ShootComp::addBullet_toList(GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess) {

	fire();

	/*
	if (is_there_ammo()) {
		start_position = glm::vec3(carPos.x, carPos.y-0.2f, carPos.z);
		Direction_x = x;
		Direction_y = y;
		Direction_z = z;
		uniformModel = uniModel;
		uniformShininess = uniShininess;
		uniformSpecularIntensity = uniSpecularIntensity;

		Bullet tmp_bullet = Bullet();
		tmp_bullet.createBullet(start_position, uniformModel, uniformSpecularIntensity, uniformShininess, Direction_x, Direction_y, Direction_z);

		bulletsList.push_back(tmp_bullet);

	}
	*/
}
void ShootComp::addBullet_toList(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess, float x, float y, float z) {

	fire();

	if (is_there_ammo()) {
		start_position = glm::vec3(carPos.x, carPos.y - 0.2f, carPos.z);
		Direction_x = x;
		Direction_y = y;
		Direction_z = z;
		uniformModel = uniModel;
		uniformShininess = uniShininess;
		uniformSpecularIntensity = uniSpecularIntensity;

	    glm::vec3 start_pos2 =glm::vec3(start_position.x+5.f*Direction_x, start_position.y + 5.f*Direction_y, start_position.z + 5.f*Direction_z);
		glm::vec3 start_pos3 = glm::vec3(start_pos2.x + 5.f*Direction_x, start_pos2.y + 5.f*Direction_y, start_pos2.z + 5.f*Direction_z);

		Bullet tmp_bullet = Bullet();
		Bullet tmp_bullet2 = Bullet();
		Bullet tmp_bullet3 = Bullet();
		tmp_bullet.createBullet(start_position, uniformModel, uniformSpecularIntensity, uniformShininess, Direction_x, Direction_y, Direction_z);

		tmp_bullet.createBullet(start_position, uniformModel, uniformSpecularIntensity, uniformShininess, Direction_x, Direction_y, Direction_z);
		tmp_bullet2.createBullet(start_pos2, uniformModel, uniformSpecularIntensity, uniformShininess, Direction_x, Direction_y, Direction_z);
		tmp_bullet3.createBullet(start_pos3, uniformModel, uniformSpecularIntensity, uniformShininess, Direction_x, Direction_y, Direction_z);
		std::cout << "All 2 bullets CREATED \n";

		bulletsList.push_back(tmp_bullet);
		bulletsList.push_back(tmp_bullet2);
		bulletsList.push_back(tmp_bullet3);
	}

}
void ShootComp::renderAllBullets() {
	auto b = bulletsList.begin();
	while (b != bulletsList.end()) {
		if ((b)->isDead())
			bulletsList.erase(b++);
		else {
			(b)->renderBullet();
			++b;
		}
	}
}
void ShootComp::updatePosition(glm::vec3 newpos) {
	start_position = newpos;
}

void ShootComp::updateDirection(float x, float y, float z) {
	Direction_x = x;
	Direction_y = y-0.3f;
	Direction_z = z;
}

void ShootComp::fire() {
	if (ammo > 0) {
		ammo -= 1;
	}
	
	std::cout << "Bulled fired!  Bullet counter = " << ammo<<"\n";
}

void ShootComp::recharge() {
	ammo +=10;
}
bool ShootComp::is_there_ammo() {
	if (ammo > 0) { return true; }
	else { return false; }
}

void ShootComp::Tick(float deltaTime) {}