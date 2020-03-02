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

	update();
}

void Camera::calculateAngleAroundTarget(float xChange) {
	angleAroundTarget += (xChange * turnSpeed) ;
/*
	if (angleAroundTarget < -30.f)
		angleAroundTarget = -30.f;
	if (angleAroundTarget > 30.f)
		angleAroundTarget = 30.f;
		*/
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

	std::cout << "pitch: " << pitch << " yaw: " << yaw << std::endl;
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

void Camera::stickControl(GLfloat xChange, GLfloat yChange, bool reset, glm::vec3 carPos, glm::vec3 dir) {
	if (reset) {
		setFront(dir.x, -0.5, dir.z);
		angleAroundTarget = 0;
		return;
	}

	float angleAroundY = glm::degrees(atan2(dir.z, dir.x));
	calculateAngleAroundTarget(xChange);
	calculatePos(carPos, angleAroundY + angleAroundTarget);
	std::cout << "y " << angleAroundY << std::endl;
	yaw = angleAroundY + angleAroundTarget;


	update();
}

void Camera::calculatePos(glm::vec3 carPos, float theta) {
	position.y = carPos.y + 2.f;


	float xOffset = distance * sin(glm::radians(theta));
	float zOffset = distance * cos(glm::radians(theta));

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

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}
