#include "DamageComponent.h"

DamageComponent::DamageComponent() {}

DamageComponent::DamageComponent(double d) : localDamage(d) {}

double DamageComponent::GetDamage() {
	return localDamage;
}

void DamageComponent::SetDamage(double d) {
	localDamage = d;

	return;
}

void DamageComponent::Tick(float deltaTime) {}