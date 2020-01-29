#pragma once

#include "Component.h"

/*
* HealthComponent class inherits from Component class, representing the health of the bound object
*/
class HealthComponent : public Component
{
public:
	HealthComponent();
	HealthComponent(double h);
	~HealthComponent();

	void Tick(float deltaTime);
	double GetHealth();
	void SetHealth(double h);

private:
	double localHealth;
};

