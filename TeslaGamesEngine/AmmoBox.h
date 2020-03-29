#pragma once
#include "PhysicsObject.h"
#include <GLFW\glfw3.h>	//needed for time

class AmmoBox :
	public PhysicsObject
{
public:
	AmmoBox();

	//true if the box has already been picked up, false otherwise
	bool getIsPicked() { return isPicked; }
	void setIsPicked();

	//like a tick function, does an alive check and updates current time
	void timeRespawnCheck();


private:
	bool isPicked;	//tells us if the box is "dead"
	float deathDuration, currentTime, timeOfDeath;
	void updateTime();		//updates current time

	void respawnBox();	//resets necessary values to bring box back to life
};

