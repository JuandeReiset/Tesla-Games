#include "ShootComp.h"
ShootComp::ShootComp() {}
ShootComp::ShootComp(int am): ammo(am)  {}
ShootComp::~ShootComp() {};

double ShootComp::getBulletSpeed() {
	return bullet_speed;
}

double ShootComp::getBulletDir() {
	return bullet_direction;

}

void ShootComp::SetBulletDirection(double h) {
	bullet_direction = h;

	return;
}

void ShootComp::SetBulletSpeed(double h) {
	bullet_speed = h;

	return;
}

void ShootComp::fire() {


	if (ammo <= 0) {
		ammo = 0;
	}
	else {
		ammo = ammo - 1;
	}
	return;
}

void ShootComp:: refill_ammo() {
	ammo = ammo + 10;
}

int ShootComp::get_ammo_counter() {
	return ammo;
}
void ShootComp::Tick(float deltaTime) {}