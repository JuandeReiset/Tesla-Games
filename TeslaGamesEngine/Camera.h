#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

#include "Component.h"

/*
 * Class representing a camera in the game
 */
class Camera : public Component
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::vec3 getCameraCenter();
	glm::vec3 front;
	void setPosition(float x, float y, float z);
	void setCenter(float x, float y, float z);

	glm::mat4 calculateViewMatrix();

	// Camera's frame update
	void Tick(float deltaTime);

	~Camera();

private:
	glm::vec3 position;

	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};

