#include "pch.h"
#include "Component.h"


Component::Component()
{
}

Component::Component(Transform t)
{
	localTransform = t;
}

Transform Component::GetTransform()
{
	return localTransform;
}

void Component::SetTransform(Transform t)
{
	localTransform = t;
}


Component::~Component()
{
}
