#pragma once

#include "Component.h"
#include "audioEngine.h"
#include "Global.h"

/*
* HealthComponent class inherits from Component class, representing the health of the bound object
*/
class HealthComponent : public Component
{
public:
	HealthComponent();
	HealthComponent(double h);
	~HealthComponent();

	void setPosition(float x, float y, float z);

	void Tick(float deltaTime);
	double GetHealth();
	void SetHealth(double h);

	void initAudioForHealthComponent(AudioEngine* engine);

	void audioUpdate();

	void takeDamageFromBullet(float damageVal);

	void takeTrapDamage(float damageVal);

private:
	double localHealth;
	AudioEngine* audioEngine;
	AudioBoomBox bulletHitEffect;
	AudioBoomBox trapDamageEffect;

	float posX;
	float posY;
	float posZ;
};

