#include "pch.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Transform t)
{
	transform = t;
}


Transform Object::GetTransform()
{
	return transform;
}

void Object::SetTransform(Transform t)
{
	transform = t;
}

Object::~Object()
{
}
