#include "Oil.h"

Oil::Oil(int idInput) {
	id = idInput;
	life = 5.f;											//lifetime is 5 sec
	birthTime = glfwGetTime();
	currentTime = glfwGetTime();

	oilObj.LoadModel("Models/caltrops.obj");
	model = glm::mat4(1.f);
	uniformModel = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;

	shinyMaterial = Material(4.0f, 256);
}

bool Oil::isDead() {
	updateTime();
	if (currentTime - birthTime >= life)
		return true;
	else
		return false;
}

void Oil::updateTime() {
	currentTime = glfwGetTime();
}

void Oil::createOil(glm::vec3 carPos) {
	position = glm::vec3(carPos.x, carPos.y - 1.2f, carPos.z);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));

}

void Oil::load(GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess) {
	uniformModel = uniModel;
	uniformShininess = uniShininess;
	uniformSpecularIntensity = uniSpecularIntensity;
}

void Oil::renderOil() {
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

	oilObj.RenderModel();
}

Oil::~Oil() {

}