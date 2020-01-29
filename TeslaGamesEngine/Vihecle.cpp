#include "Vihecle.h"

Vihecle::Vihecle() {}
Vihecle::~Vihecle() {}

void Vihecle::Tick(float deltaTime) {}

double Vihecle::currentHealth(float deltaTime) {
	return health.GetHealth();
}

void Vihecle::getDamage(float deltaTime, double damage) {
	double h = health.GetHealth();
	health.SetHealth(h - damage);

	return;
}