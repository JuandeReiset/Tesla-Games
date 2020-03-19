#include "PickupBox.h"

PickupBox::PickupBox() {
	isPicked = false;
	deathDuration = 8.0f;
	timeOfDeath = 0;
	currentTime = glfwGetTime();
}

void PickupBox::setIsPicked() {
	isPicked = true;
	timeOfDeath = glfwGetTime();
}

void PickupBox::updateTime()
{
	currentTime = glfwGetTime();
}

void PickupBox::timeRespawnCheck()
{
	updateTime();

	//box is currently dead and ready to respawn
	if (getIsPicked() && (currentTime - timeOfDeath >= deathDuration)) {
		respawnBox();
	}
}

void PickupBox::respawnBox()
{
	isPicked = false;
	timeOfDeath = 0;
}
