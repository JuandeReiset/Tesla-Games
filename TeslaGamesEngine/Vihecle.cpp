#include "Vihecle.h"
#include <iostream>

Vihecle::Vihecle() {}
Vihecle::Vihecle(int id) : ID(id) {}
Vihecle::~Vihecle() {}

void Vihecle::Tick(float deltaTime) {
	std::cout << "Current health:" << currentHealth() << std::endl;
	if (currentHealth() <= 0)
		dead_flag = 1;

	if (ID == combat.GetTargetID())
		getDamage(combat.GetDamage());
}

double Vihecle::currentHealth() {
	return health.GetHealth();
}

void Vihecle::getDamage(double damage) {
	double h = health.GetHealth();
	health.SetHealth(h - damage);

	return;
}