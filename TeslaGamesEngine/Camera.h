#pragma once

#include "Component.h"

/*
 * Class representing a camera in the game
 */
class Camera : public Component
{
public:
	Camera();

	// Camera's frame update
	void Tick(float deltaTime);

	// New transform for the camera

	void MoveCamera(Transform moveTo);
	// TODO: Uncomment and define after getting OpenGL working
	// glm::mat4 GetViewMatrix();
	~Camera();

private:
	float moveSpeed;
	float turnSpeed;
};

