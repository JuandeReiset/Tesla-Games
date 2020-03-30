#include "Smoke.h"

Smoke::Smoke(int idInput, float duration) {
	id = idInput;
	life = duration;											//lifetime is 5 sec
	birthTime = glfwGetTime();
	currentTime = glfwGetTime();

	smokeObj.LoadModel("Models/smoke.obj");
	model = glm::mat4(1.f);
	uniformModel = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;

	shinyMaterial = Material(4.0f, 256);
}

bool Smoke::isDead() {
	if (life <= -1.f) {
		return false;
	}
	else {
		updateTime();
		if (currentTime - birthTime >= life)
			return true;
		else
			return false;
	}
}

void Smoke::updateTime() {
	currentTime = glfwGetTime();
}

void Smoke::createSmoke(glm::vec3 carPos) {
	position = glm::vec3(carPos.x, carPos.y - 1.2f, carPos.z);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));

}

void Smoke::load(GLuint uniModel, GLuint uniSpecularIntensity, GLuint uniShininess) {
	uniformModel = uniModel;
	uniformShininess = uniShininess;
	uniformSpecularIntensity = uniSpecularIntensity;
}

void Smoke::renderSmoke() {
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

	smokeObj.RenderModel();
}

Smoke::~Smoke() {

}