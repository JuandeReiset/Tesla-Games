#include "Combat.h"

void Combat::SetTargetID(int id) {
	targetID = id;

	return;
}

void Combat::SetDamage(double d) {
	damage = d;

	return;
}

int Combat::GetTargetID() {
	return targetID;
}

double Combat::GetDamage() {
	return damage;
}

