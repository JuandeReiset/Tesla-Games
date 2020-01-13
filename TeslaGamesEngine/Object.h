#pragma once

#include "Transform.h"
#include "Entity.h"

/*
 * Abstract class representing game objects in the world
 */
class Object
{
public:
	Object();
	Object(Transform t);
	// Frame update function for all objects to overrirde
	virtual void Tick(float deltaTime) = 0;

	virtual Transform GetTransform() = 0;
	virtual void SetTransform() = 0;
	~Object();

private:
	// Absolute position/rotation of an object in the world
	Transform transform;
	// When extending an object, list it's entity as private variable and include Getters/Setters
};

