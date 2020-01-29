#include "DamagingObject.h"

DamagingObject::DamagingObject() {}
DamagingObject::DamagingObject(double d) : damage(d) {}
DamagingObject::~DamagingObject() {}

void DamagingObject::Tick(float deltaTime) {}

double DamagingObject::sendDamage(float deltaTime) {
	return damage.GetDamage();
}