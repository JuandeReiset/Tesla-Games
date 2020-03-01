#include "Caltrops.h"

Caltrops::Caltrops() {
	life = 5.f;											//lifetime is 5 sec
	birthTime = glfwGetTime();
	currentTime = glfwGetTime();

	caltropsObj.LoadModel("Models/caltrops.obj");
	model = glm::mat4(1.f);
	uniformModel = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;

	shinyMaterial = Material(4.0f, 256);
}

bool Caltrops::isDead() {
	updateTime();
	if (currentTime - birthTime >= life)
		return true;
	else
		return false;
}

void Caltrops::updateTime() {
	currentTime = glfwGetTime(); 
}

void Caltrops::createCaltrops(glm::vec3 carPos, GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess) {
	position = glm::vec3(carPos.x, carPos.y - 1.5f, carPos.z);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

	uniformModel = uniModel;
	uniformShininess = uniShininess;
	uniformSpecularIntensity = uniSpecularIntensity;
}

void Caltrops::renderCaltrops() {
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

	caltropsObj.RenderModel();
}

Caltrops::~Caltrops() {

}