#pragma once

#include "Transform.h"
#include "Component.h"

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

	Transform GetTransform();
	void SetTransform(Transform t);
	~Object();

protected:
	// Absolute position/rotation of an object in the world
	Transform transform;
	// When extending an object, list it's entity as private variable and include Getters/Setters
};

