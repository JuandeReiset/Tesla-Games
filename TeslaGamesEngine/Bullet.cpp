#include "Bullet.h"

Bullet::Bullet() {
	life = 5.f;											//lifetime is 5 sec
	birthTime = glfwGetTime();
	currentTime = glfwGetTime();

	BulletObj.LoadModel("Models/bullet.obj");
	model = glm::mat4(1.f);
	uniformModel = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;

	shinyMaterial = Material(4.0f, 256);
}

bool Bullet::isDead() {
	updateTime();
	if (currentTime - birthTime >= life)
		return true;
	else
		return false;
}

void Bullet::updateTime() {
	currentTime = glfwGetTime();
}

void Bullet::createBullet(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess,float Dir_x, float Dir_y, float Dir_z) {
	position = glm::vec3(carPos.x, carPos.y + 0.5f, carPos.z);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

	bullet_speed = 5.f;
	Direction_x = Dir_x;
	Direction_y = Dir_y;
	Direction_z = Dir_z;
	uniformModel = uniModel;
	uniformShininess = uniShininess;
	uniformSpecularIntensity = uniSpecularIntensity;
}

void Bullet::renderBullet() {
	
	shoot_distance_x += Direction_x * bullet_speed;
	shoot_distance_y += Direction_y * bullet_speed -0.01f;
	shoot_distance_z += Direction_z * bullet_speed;

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x + shoot_distance_x, position.y+0.5f+shoot_distance_y, position.z + shoot_distance_z));

	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	
	

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

	BulletObj.RenderModel();
}
/*
Bullet::~Bullet() {

}
*/