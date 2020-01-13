#include "pch.h"
#include "Entity.h"


Entity::Entity()
{
}

Entity::Entity(Transform t)
{
	localTransform = t;
}

Transform Entity::GetTransform()
{
	return localTransform;
}

void Entity::SetTransform(Transform t)
{
	localTransform = t
}


Entity::~Entity()
{
}
