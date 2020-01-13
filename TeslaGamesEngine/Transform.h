#pragma once

/*
 * Quaternion used for storing rotation
 */
struct Quaternion {
	float w, x, y, z;

	Quaternion() {
		w, x, y, z = 0;
	}

	Quaternion(float w_, float x_, float y_, float z_) {
		w = w_;
		x = x_;
		y = y_;
		z = z_;
	}
};

/*
 * 3d Vector used for storing position
 */
struct Vector3 {
	float x, y, z;

	Vector3() {
		x, y, z = 0;
	}

	Vector3(float x_, float y_, float z_) {
		x = x_;
		y = y_;
		z = z_;
	}
};

/*
 * Class representing the position and rotation of objects and components
 */
class Transform
{
public:
	Transform();
	Transform(Vector3 aPos, Quaternion aRot);

	void SetPosition(Vector3 newPos);
	void SetRotation(Quaternion newRot);
	Vector3 GetPosition();
	Quaternion GetRotation();

	// TODO: After getting PhysX and OpenGL working, write these functions
	// Transform to glm model matrix
	// Transform to physx transform
	// Transform from physx transform

	~Transform();

private:
	Vector3 position;
	Quaternion rotation;
};

