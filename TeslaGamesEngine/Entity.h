#pragma once

#include "Transform.h"

/*
 * Abstract class representing game entities in the world
 * Entities are attached to objects and have relative tranforms to those objects
 */
class Entity
{
public:
	Entity();
	Entity(Transform t);
	// This is the frame update function every entity should override
	virtual void Tick(float deltaTime) = 0;
	Transform GetTransform();
	void SetTransform(Transform t);
	~Entity();

private:
	// This is the relative transform of the entity to it's parent object
	Transform localTransform;
};

