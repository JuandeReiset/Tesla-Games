#pragma once
#include "Component.h"

class ShootComp :
	public Component
{
	public:
		ShootComp();
		ShootComp(int ammo);
		~ShootComp();

		
		double getBulletSpeed();
		double getBulletDir();     //Need to change to proper direction value
		void SetBulletSpeed(double h);
		void SetBulletDirection(double p);

private:
	double bullet_speed;
	double bullet_direction;   // Need to change to proper direction value
	int ammo;
};

