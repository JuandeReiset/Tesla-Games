#pragma once

#include "Object.h"
#include "HealthComponent.h"

/*
 * Vihecle class inherits from Object class, with values like health, speed, etc.
 */
class Vihecle : public Object
{
public:
	Vihecle();
	~Vihecle();

	void Tick(float deltaTime);
	double currentHealth(float deltaTime);
	void getDamage(float deltaTime, double damage);

private:
	HealthComponent health = HealthComponent(100);
};

