#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle() {}
Vehicle::Vehicle(int id) : ID(id) {}
Vehicle::~Vehicle() {}

void Vehicle::Tick(float deltaTime) {
	std::cout << "Current health:" << currentHealth() << std::endl;
	if (currentHealth() <= 0)
		dead_flag = 1;

	if (ID == combat.GetTargetID())
		getDamage(combat.GetDamage());
}

double Vehicle::currentHealth() {
	return health.GetHealth();
}

void Vehicle::getDamage(double damage) {
	double h = health.GetHealth();
	health.SetHealth(h - damage);

	return;
}