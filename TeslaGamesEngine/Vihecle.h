#pragma once

#include "Object.h"
#include "HealthComponent.h"
#include "Global.h"

/*
 * Vihecle class inherits from Object class, with values like health, speed, etc.
 */
class Vihecle : public Object
{
public:
	Vihecle();
	Vihecle(int id);
	~Vihecle();

	void Tick(float deltaTime);
	double currentHealth();
	void getDamage(double damage);

private:
	HealthComponent health = HealthComponent(100);
	int ID;															//each vihecle has a unique number for recognizition
};

