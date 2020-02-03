#pragma once

#include "Object.h"
#include "HealthComponent.h"
#include "Global.h"

/*
 * Vehicle class inherits from Object class, with values like health, speed, etc.
 */
class Vehicle : public Object
{
public:
	Vehicle();
	Vehicle(int id);
	~Vehicle();

	void Tick(float deltaTime);
	double currentHealth();											//get the current health
	void getDamage(double damage);									//get damage for damaging object

private:
	HealthComponent health = HealthComponent(100);
	int ID;															//each vihecle has a unique number for recognizition
};

