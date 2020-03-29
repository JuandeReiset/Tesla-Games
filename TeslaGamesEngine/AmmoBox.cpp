#include "AmmoBox.h"

AmmoBox::AmmoBox() {
	isPicked = false;
	deathDuration = 8.0f;
	timeOfDeath = 0;
	currentTime = glfwGetTime();
}

void AmmoBox::setIsPicked() {
	isPicked = true;
	timeOfDeath = glfwGetTime();
}

void AmmoBox::updateTime()
{
	currentTime = glfwGetTime();
}

void AmmoBox::timeRespawnCheck()
{
	updateTime();

	//box is currently dead and ready to respawn
	if (getIsPicked() && (currentTime - timeOfDeath >= deathDuration)) {
		respawnBox();
	}
}

void AmmoBox::respawnBox()
{
	isPicked = false;
	timeOfDeath = 0;
}
