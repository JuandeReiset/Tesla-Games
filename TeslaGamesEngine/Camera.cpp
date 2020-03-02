#include "pch.h"
#include "Camera.h"

#include <iostream>

Camera::Camera()
{
}

void Camera::Tick(float deltaTime)
{
	// Update camera based on mouse/joystick moves
}


//front is a vector for camera direction
Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	distance = 5.0f;
	angleAroundTarget = 0;

	resetFlag = false;

	update();
}

void Camera::calculateAngleAroundTarget(float xChange) {
	angleAroundTarget += (xChange * turnSpeed) ;

	if (angleAroundTarget < -90.f)
		angleAroundTarget = -90.f;
	if (angleAroundTarget > 90.f)
		angleAroundTarget = 90.f;
		
}

void Camera::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Camera::setCenter(float x, float y, float z) {
	glm::vec3 center = glm::vec3(x, y, z);
	front = glm::normalize(center - position);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
void Camera::setFront(float x, float y, float z) {
	front = glm::vec3(x, y, z);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	
	pitch = -15;
	yaw = glm::degrees(atan2(front.z, front.x));
}



void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

void Camera::stickControl(GLfloat xChange, GLfloat yChange, glm::vec3 carPos, glm::vec3 dir) {
	bool reset = false;
	float angleAroundY = glm::degrees(atan2(dir.z, dir.x));
	if (xChange == 0)
		reset = true;

	if (resetFlag) {
		if (abs(angleAroundTarget) < turnSpeed) {
			angleAroundTarget = 0;

			resetFlag = false;
		}
		else {
			if (angleAroundTarget > 0)
				angleAroundTarget -= turnSpeed;
			else if (angleAroundTarget < 0)
				angleAroundTarget += turnSpeed;
		}
	}
	else {
		if (reset) {
			if (abs(angleAroundTarget) < turnSpeed) {
				angleAroundTarget = 0;
				resetFlag = false;
			}
			else {
				if (angleAroundTarget > 0)
					angleAroundTarget -= turnSpeed;
				else if (angleAroundTarget < 0)
					angleAroundTarget += turnSpeed;
			}

			resetFlag = true;
		}
		else {
			calculateAngleAroundTarget(xChange);
		}
	}

	calculatePos(carPos, angleAroundY + angleAroundTarget);
	yaw = angleAroundY + angleAroundTarget;
	update();
}

void Camera::calculatePos(glm::vec3 carPos, float theta) {
	position.y = carPos.y + 2.f;

	std::cout << "y " << theta << std::endl;

	float xOffset = distance * cos(glm::radians(theta));
	float zOffset = distance * sin(glm::radians(theta));

	position.x = carPos.x - xOffset;
	position.z = carPos.z - zOffset;
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::vec3 Camera::getCameraCenter() {
	return getCameraDirection() + front;
}
glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::initializeAudio(AudioEngine* engine) {
	this->audioEngine = engine;
}
void Camera::updateListenerPosition() {
	this->audioEngine->updateListenerPosition(position.x, position.y, position.z);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	updateListenerPosition();
}

Camera::~Camera()
{
}
