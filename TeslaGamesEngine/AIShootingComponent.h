#pragma once
#include "ShootComp.h"
#include "Raycast_shooting.h"
#include "Vehicle.h"
#include "Track.h"
#include <glm\glm.hpp>

enum class AimingState
{
	Reloading,
	NoTarget,
	Aiming,
	Locked,
	NoAmmo
};

class AIShootingComponent
{
public:
	AIShootingComponent();
	void Tick(float deltaTime);
	AIShootingComponent(Vehicle* v);

	void Aim();
	void SetVehicles(std::vector<Vehicle*> vehiclesToSet);
	void SetTrack(Track* t) { racetrack = t; }

	// TODO: Remove. This is for testing
	void SetTarget(Vehicle* v) { target = v; }

	void SetUniformLocations(GLuint model, GLuint spec, GLuint shine);

	~AIShootingComponent();

	int wantToPlaceTrap;
	Vehicle* owner;

	bool shouldUseAbility;
	float lastAbilityTime;
	float abilityCooldownTime;

private:
	Vehicle* FindTarget();
	bool IsTargetInView(Vehicle* aTarget);
	bool IsVehicleBehind(Vehicle* aTarget);
	bool IsReloading();
	void FindAimingState();
	bool AimAtTarget();
    glm::vec3 Shootdir;
	std::vector<Vehicle*> vehicles;
	
	Vehicle* target;
	AimingState aimingState;
	float threshold;
	Track* racetrack;

	float lastFiredTime;



	Raycast_shooting raycast_handler;

	GLuint uniformModel = 0;
	GLuint uniformSpecular= 0;
	GLuint uniformShininess = 0;
};

