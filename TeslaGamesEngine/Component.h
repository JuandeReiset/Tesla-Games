#pragma once

#include "Transform.h"

// TODO: Extend a SoundComponent, DrawableComponent, PhysicsComponent from Component and then extended from those to create other relevant components
// This is to allow a switch based on the "parent" component type so we can send info to the relevant systems

/*
 * Abstract class representing game entities in the world
 * Entities are attached to objects and have relative tranforms to those objects
 */
class Component
{
public:
	Component();
	Component(Transform t);
	// This is the frame update function every entity should override
	virtual void Tick(float deltaTime) = 0;
	Transform GetTransform();
	void SetTransform(Transform t);
	~Component();

protected:
	// This is the relative transform of the entity to it's parent object
	Transform localTransform;
};

