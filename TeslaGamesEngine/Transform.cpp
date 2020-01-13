#include "pch.h"
#include "Transform.h"


Transform::Transform()
{
	position = Vector3();
	rotation = Quaternion();
}

Transform::Transform(Vector3 aPos, Quaternion aRot)
{
	position = aPos;
	rotation = aRot;
}

void Transform::SetPosition(Vector3 newPos)
{
	position = newPos;
}

void Transform::SetRotation(Quaternion newRot)
{
	rotation = newRot;
}

Vector3 Transform::GetPosition()
{
	return position;
}

Quaternion Transform::GetRotation()
{
	return rotation;
}


Transform::~Transform()
{
}
