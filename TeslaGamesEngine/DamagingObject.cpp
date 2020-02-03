#include "DamagingObject.h"

DamagingObject::DamagingObject() {}
DamagingObject::DamagingObject(double d, int id) : damage(d), targetID(id) {}
DamagingObject::~DamagingObject() {}

void DamagingObject::Tick(float deltaTime) {
	combat.SetTargetID(targetID);
	combat.SetDamage(sendDamage());

	return;
}

int DamagingObject::GetTargetId() {
	return targetID;
}

void DamagingObject::SetTargetId(int id) {
	targetID = id;

	return;
}

double DamagingObject::sendDamage() {
	return damage.GetDamage();
}