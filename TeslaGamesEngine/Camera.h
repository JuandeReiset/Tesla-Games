#pragma once

#include "Entity.h"

/*
 * Class representing a camera in the game
 */
class Camera : public Entity
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
	Transform transform;
	float moveSpeed;
	float turnSpeed;
};

