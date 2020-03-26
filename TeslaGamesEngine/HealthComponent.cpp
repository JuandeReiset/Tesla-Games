#include "HealthComponent.h"

HealthComponent::HealthComponent(){}
HealthComponent::HealthComponent(double h) : localHealth(h) {}
HealthComponent::~HealthComponent() {};

double HealthComponent::GetHealth() {
	return localHealth;
}

void HealthComponent::SetHealth(double h) {
	localHealth = h;

	return;
}

void HealthComponent::initAudioForHealthComponent(AudioEngine* engine) {
	this->audioEngine = engine;
	this->bulletHitEffect = this->audioEngine->createBoomBox(audioConstants::SOUND_FILE_HIT_BULLET);
	this->trapDamageEffect = this->audioEngine->createBoomBox(audioConstants::SOUND_FILE_HIT_TRAP);

	float initialSoundVolume = 15.f;

	this->bulletHitEffect.setVolume(initialSoundVolume);
	this->trapDamageEffect.setVolume(initialSoundVolume);
}

void HealthComponent::audioUpdate() {
	this->bulletHitEffect.updateSourcePosition(this->posX, this->posY, this->posZ);
	this->trapDamageEffect.updateSourcePosition(this->posX, this->posY, this->posZ);
}

void HealthComponent::takeDamageFromBullet(float damageVal) {
	this->localHealth = this->localHealth - damageVal;
	this->bulletHitEffect.playSound();
}
void HealthComponent::takeTrapDamage(float damageVal) {
	this->localHealth = this->localHealth - damageVal;
	this->trapDamageEffect.playSound();
}
void HealthComponent::setPosition(float x, float y, float z) {
	this->posX = x;
	this->posY = y;
	this->posZ = z;
	this->audioUpdate();
}

void HealthComponent::Tick(float deltaTime){}
